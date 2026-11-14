# Testing and Validation

This is a test plan. Outcomes are marked not recorded until measured evidence is added.

| ID | Test | Procedure | Expected result | Result |
|---|---|---|---|---|
| T01 | Power-up | Power assembled circuit | Board boots without abnormal heating | Not recorded |
| T02 | Sensor detection | Inspect serial output | Valid temperature, not disconnected-sensor code | Not recorded |
| T03 | Sensor fault | Safely disconnect sensor data | Fault reported; no false temperature alert | Not recorded |
| T04 | LCD | Observe display | Temperature/status is legible | Not recorded |
| T05 | Wi-Fi | Enter valid credentials | Connected status and IP printed | Not recorded |
| T06 | Dashboard | Browse to IP on same network | Page loads and reading is shown | Not recorded |
| T07 | Threshold validation | Submit valid/invalid values | Valid accepted; invalid rejected | Not recorded |
| T08 | Local alarm | Controlled test above threshold | Buzzer activates | Not recorded |
| T09 | Alert latch | Keep reading above threshold | No repeated request after successful alert | Not recorded |
| T10 | Re-arm | Return below threshold and cross again | New event can notify | Not recorded |
| T11 | Twilio | Call protected test Function | SMS and call delivered to authorized test recipient | Not recorded |
| T12 | Network failure | Interrupt network | Local sensing/alarm continues; remote failure logged | Not recorded |

## Debugging note
During prototype debugging, a 47-ohm pull-up was associated with DS18B20 detection failure. Replacing it with 1-kilohm allowed detection. A 4.7-kilohm pull-up is a conventional alternative to validate.

## Evidence to add
Add circuit photographs, serial output, dashboard screenshot and redacted notification evidence. Hide Wi-Fi details, phone numbers, Twilio identifiers and secrets.
