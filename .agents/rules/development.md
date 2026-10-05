# Embedded development

## C++ / Arduino conventions

1. Prefer non-blocking `millis()`-based timing over `delay()` where possible.
2. Avoid dynamic allocation (`malloc`, `new`) on resource-constrained microcontrollers; prefer static or stack storage.
3. Prefer `const` values and `enum` over preprocessor macros when appropriate.
4. Explain code intent in concise Japanese comments, following the existing firmware convention. Agent instruction documents themselves must be in English.

## Board-specific libraries

- Use the Wio-compatible TFT_eSPI configuration for Wio Terminal display work.
- Follow the target project's existing network libraries. Do not copy board initialization from a different board without checking compatibility.
