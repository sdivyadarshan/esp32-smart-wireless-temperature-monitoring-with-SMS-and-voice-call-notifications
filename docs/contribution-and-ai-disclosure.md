# Contribution and AI Assistance Disclosure

## Project-owner contributions
Based on the project development discussions:
- Selected and developed the smart wireless temperature-monitoring project concept.
- Selected and assembled the ESP32, DS18B20, LCD and buzzer hardware.
- Performed physical wiring and prototype troubleshooting.
- Investigated DS18B20 detection failure and tested changing the pull-up from 47 ohms to 1 kilohm.
- Tested the Twilio Function endpoint and observed prototype behavior.
- Made project-level decisions about local display, browser dashboard and remote alert behavior.

## AI-assisted work
AI assistance was used for:
- Firmware structuring and refinement.
- ESP32-hosted dashboard and threshold-handling implementation guidance.
- HTTPS/Twilio Function integration guidance.
- README, architecture, algorithm, design-decision and testing documentation drafting.
- Reviewing implementation limitations and security considerations.

## Verification responsibility
The project owner should review and understand the code, compile and test it on the actual hardware, and update test outcomes with evidence. AI-assisted code should not be represented as independently authored or fully validated unless that is accurate.

## Portfolio explanation
“I designed and assembled an ESP32-based temperature-monitoring prototype using a DS18B20 sensor, I2C LCD and buzzer. I debugged the sensor interface and integrated a local web dashboard with configurable threshold monitoring. For remote notifications, the ESP32 sends an HTTPS request to a Twilio cloud Function, which triggers SMS and an automated voice call. AI tools assisted with parts of firmware refinement and technical documentation; I validated hardware behavior during prototype testing.”
