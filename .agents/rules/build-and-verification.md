# Build and verification

Prefer Arduino CLI commands for compilation, upload, and dependency management. See [the shared Arduino guide](../../docs/arduino-development.md) and the affected project's README for setup and exact board configuration.

```sh
arduino-cli board list
arduino-cli core list
arduino-cli lib list
arduino-cli compile --fqbn <FQBN> <SKETCH_DIRECTORY>
arduino-cli upload -p <PORT> --fqbn <FQBN> <SKETCH_DIRECTORY>
```

- Use the target board's actual FQBN. Do not infer compatibility from a chip-family directory or copy another board's settings. For boards with multiple cores, follow the project's documented core.
- Discover the connected port with `arduino-cli board list`; do not assume a Windows COM port or a Linux device name on macOS.
- Compile affected firmware when source or build configuration changes and dependencies are available. Run relevant local checks for cloud/Python changes using that project's documented environment.
- For documentation, directory, and editor-setting changes, check JSON syntax, relative links, Git diffs, and preservation of moved source/assets. A hardware build is unnecessary for a pure documentation/configuration change.
- Distinguish compilation, local execution, and physical hardware verification in the result. Report unavailable dependencies or hardware checks instead of claiming they passed.
- Firmware upload changes a connected device; cloud deployment changes an external service. Perform them when included in the user's requested scope.
- If Arduino CLI fails, inspect its error, installed cores/libraries, and project configuration before changing the environment. Do not delete caches, stop unrelated processes, or reinstall tools as a routine first step.
