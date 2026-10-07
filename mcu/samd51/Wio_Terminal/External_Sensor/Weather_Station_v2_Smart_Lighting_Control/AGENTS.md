# Project instructions

Follow the [root instructions](../../../../../AGENTS.md) and their referenced rules. These instructions apply to this integrated project only.

## Scope

- Compile with the installed Seeed SAMD core identifier `Seeeduino:samd:seeed_wio_terminal` (capital S). Confirm it with Arduino CLI board discovery if the environment changes.
- Build this integration by adding lighting functions to the original Weather Station v2 sketch. Preserve its weather readings, publication payloads, three-section LCD layout, sprite rendering, and Free Font selections; copy `Free_Fonts.h` unchanged into the integrated sketch folder. Do not replace the weather implementation or display with a rewritten version without an explicit request. Keep lighting additions in `lighting_control.h` and configuration in `config.h`; preserve the original weather and Adafruit IO MQTT clients, and use a separate MQTT client for the lighting Shiftr instance. Report lighting ADC readings and feedback through Serial Monitor rather than changing the existing weather display.
- Keep this project separate from `../Weather_Station_v2/`. Do not change the original weather project as part of integrated-project edits unless explicitly requested.
- The Chassis Battery is required for this documented setup. Use its Grove ports: light sensor D0/A0 (shared with D1/A1), IR emitter D2/A2 (shared with D3/A3), and IR receiver D4/A4 (shared with D5/A5). BME280 remains on the Terminal's Grove I2C port.
- Battery charge/voltage display was removed at the user's request. Do not reintroduce its firmware, dependencies, configuration, or README instructions without a new request.
- Preserve compatibility with MQTT settings in `credentials.h`: `AIO_SERVER`, `AIO_SERVERPORT`, `SHIFTR_SERVER`, and `SHIFTR_SERVERPORT`. Include credentials before config; use guarded defaults only when these macros are absent. Do not hard-code broker endpoints at `setServer` calls or declare constants with names that conflict with these macros. Document broker edits in `credentials.h`.

## README editing rules

- Maintain `README.md` in English and `README.ja.md` in Japanese with reciprocal language links. When the user edits one language and requests synchronization, use that edited file as the reference for both content and structure. Preserve the edited source file.
- Follow the current main sections: Overview, Bill of Materials, Development, References, and Author. Under Bill of Materials, use Control System, Input & Output, Power System, and Prototyping & Wiring. Under Development, use Hardware Development, Software Development, and Test.
- Do not restore removed introductions, empty Gallery placeholders, separate Chassis Battery explanations, Arduino CLI alternatives, or session-specific verification reports merely because an older README contained them.
- Keep common weather wiring, cloud setup, analysis SQL, and references as links to the matching-language original Weather Station v2 README. Explain only the integrated project's additions locally.
- Write wiring as short `port -> component` bullets grouped under Wio Terminal and Chassis Battery. Link the official Grove port diagram beside the Chassis label. Use Grove connector labels rather than physical header-pin instructions for the standard setup.
- Write software setup as numbered actions in execution order: connect USB-C, open the exact sketch, select board and port, install libraries, edit credentials and configuration, upload, check readings/IR, then enable scheduling and upload again.
- Put each action's supplementary explanation immediately below that numbered item as an indented bullet. Do not collect notes in a distant Notes section. Name the exact file, setting, menu, and value needed for each action.
- List required libraries positively. Omit statements about unnecessary libraries or features, such as "NTPClient is not required."
- Introduce cloud integration with a short link to the existing weather setup, then show the two lighting routes in a Mermaid flowchart before the numbered steps. Preserve the identifiers `lighting`, `lighting/json`, `save_lighting_data`, `lighting_data`, and `wio_terminal_lighting`.
- Cloud steps must state the concrete actions and settings for feed/table creation, function deployment, broker selection, webhook creation, credential updates, upload, and delivery verification. Put settings and commands immediately beneath the corresponding step.
- Keep Test concise, grouping weather/cloud checks and lighting/failure checks. Link existing analysis SQL instead of copying it. Report actual verification evidence in task results; never claim unperformed compilation or hardware checks passed.
- Preserve user edits outside the requested scope. Verify relative links, section anchors, balanced code fences, matching language structure, and Git whitespace checks after editing.

## Separate Shiftr instances

- Weather uses SHIFTR_* settings and Primary Domain `weedcarpet525.cloud.shiftr.io` (display name `weather-station`). Lighting uses LIGHTING_SHIFTR_* settings and `lighting.cloud.shiftr.io`. Keep publish and subscribe operations isolated to their respective clients; reconnect lighting independently with a millis-based retry interval. Keep private credentials unchanged unless explicitly requested, and maintain the placeholder example.
