# Repository conventions

## Layout

- `mcu/<chip-family>/<board>/<project>/`: board-specific firmware and circuit diagrams.
- `sbc/<board>/<project>/`: applications and system documentation for single-board computers.
- `cloud/<runtime>/<project>/`: cloud functions and device data pipelines.
- `docs/`: repository-wide documentation.
- `.agents/rules/`: shared rules for all coding agents.
- `.agents/templates/`: reusable project documentation templates.
- `.vscode/settings.json`: shared editor settings.
- `.vscode/extensions.json`: shared extension recommendations.

See [the directory policy](directory-structure.md) for chip families, board placement, and migration paths. Arduino and XIAO remain board-level names under the corresponding chip family.

## Working conventions

- Read the project README and any nested `AGENTS.md` before changing that project. Nested instructions apply within their directory; preserve the Vision AI Camera constraints.
- Follow the user's branch instructions and preserve unrelated working-tree changes.
- Keep Arduino sketch filenames aligned with their sketch directory. Preserve existing circuit diagrams and board-specific pin mappings when reorganizing files.
- Use relative links for repository files. Update links, the root project index, and affected build paths when moving a project.
- Write project `README.md` in English and `README.ja.md` in Japanese. Maintain both together and add reciprocal language links. Explain code intent in concise Japanese comments, following the existing convention. Chat replies may follow the user's language.
- Keep root and nested agent instructions and all `.agents/` files in English. Do not create Japanese copies of agent rules or templates.
- Keep product-specific instruction files as pointers to the root `AGENTS.md`. Add shared rules here instead of duplicating them in Copilot or Claude files.

## Project documentation

Use [the project README template](../templates/project-readme.md) when adding a project; generate both English and Japanese versions from its instructions. Include an overview, architecture, bill of materials, wiring, dependencies, build/upload instructions, and verification results as applicable. Add data-flow and hardware diagrams where they help; state diagrams and timelines are optional.

Link repeated setup to the matching language of the [shared documentation](../../docs/README.md). Keep board-specific wiring, parts, configuration, and verification in each README. Do not duplicate common environment, upload, credential, or deployment procedures.

New Arduino projects normally contain `README.md`, `README.ja.md`, `sketch/<SketchName>/<SketchName>.ino`, and optional `diagrams/` and `docs/`. Add shared libraries only when there is actual shared code; check ignore patterns before introducing `lib/`, which is currently ignored.
