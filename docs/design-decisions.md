# Design Decisions

| Decision | Rationale | Trade-off |
|---|---|---|
| ESP32 controller | Integrated Wi-Fi and common embedded peripherals | Depends on network/power availability for remote alerts |
| DS18B20 | Digital OneWire sensor in waterproof probe form | Cable length, placement and conversion timing affect readings |
| I2C LCD | Two signal wires for local display | Address and logic-level compatibility must be checked |
| ESP32-hosted dashboard | No separate local server needed | Only reachable on the same accessible network |
| Wi-Fi station mode | Joins an existing router/hotspot | Network isolation can block browser access |
| Buzzer | Immediate local audible alert | Verify current and drive requirements |
| Twilio Function | Cloud service handles SMS and voice | Requires internet, configured account and may incur charges |
| Alert latch | Avoids repeated requests during one event | Requires robust retry/cooldown policy for deployment |

## Known limitations
- Firmware uses WiFiClientSecure setInsecure(), disabling TLS certificate verification. Replace with trusted CA validation.
- Dashboard uses plain HTTP and has no authentication; do not expose it to the public internet.
- Threshold is held in RAM and resets after restart.
- Cloud endpoint authentication/rate limiting must be implemented.
- Sensor faults need a dedicated fail-safe strategy.
- LCD clearing can cause flicker.
- Synchronous HTTPS calls may delay other loop work.
