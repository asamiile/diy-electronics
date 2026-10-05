# AGENTS.md

Guide for AI agents working in this repository.

This file is the shared source of truth for GitHub Copilot, OpenAI Codex, and Claude Code. Product-specific instruction files should point here instead of duplicating repository rules.

## Read first

- [.agents/rules/repository.md](.agents/rules/repository.md): directory layout, project documentation, and working conventions.
- [.agents/rules/development.md](.agents/rules/development.md): non-blocking firmware, memory use, and board-specific conventions.
- [.agents/rules/security.md](.agents/rules/security.md): credentials, examples, and ignore patterns.
- [.agents/rules/build-and-verification.md](.agents/rules/build-and-verification.md): compilation and verification.

For MQTT or cloud-pipeline changes, also read [.agents/rules/cloud-integration.md](.agents/rules/cloud-integration.md). Read the affected project's README and any nested `AGENTS.md` for its specific constraints.

## Language

Write all agent-facing files in English: root and nested `AGENTS.md`, `CLAUDE.md`, and files under `.agents/`. Keep user-facing project READMEs and shared guides bilingual (`README.md` / `README.ja.md` and matching guide variants). Agent templates use English instructions even when describing Japanese output. Chat replies may follow the user's language.

## Overview

A personal collection of DIY electronics projects using Arduino Uno, Arduino Nano ESP32, XIAO, ESP32-DevKitC, Wio Terminal, and Raspberry Pi, with related cloud data pipelines.

## Commands and configuration

- Setup and commands: [README.md](README.md).
- Directory policy: [.agents/rules/directory-structure.md](.agents/rules/directory-structure.md).
- Shared agent rules: [.agents/rules/](.agents/rules/).
- Project README template: [.agents/templates/project-readme.md](.agents/templates/project-readme.md).
- Editor settings: [.vscode/settings.json](.vscode/settings.json).
- Extension recommendations: [.vscode/extensions.json](.vscode/extensions.json).
