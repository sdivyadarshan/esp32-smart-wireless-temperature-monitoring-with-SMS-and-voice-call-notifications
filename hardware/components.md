# Hardware Components

| Component | Qty. | Function |
|---|---:|---|
| ESP32 development board | 1 | Controller, Wi-Fi and web server |
| Waterproof DS18B20 | 1 | Digital temperature sensing |
| 16x2 LCD with I2C backpack | 1 | Local temperature/status display; configured at address 0x27 |
| Active buzzer module | 1 | Audible high-temperature alert |
| Pull-up resistor | 1 | OneWire data-line pull-up |
| Breadboard and jumper wires | As needed | Prototyping |
| USB cable/power source | 1 | Programming and power |

## Pull-up resistor debugging
The project debugging record states that a 47-ohm resistor caused sensor detection failure and replacing it with 1-kilohm allowed the sensor to be detected. A 4.7-kilohm pull-up is the conventional DS18B20 starting value and is a useful alternative to validate with the actual cable and circuit.

Check the LCD backpack logic-level requirements and ensure the buzzer current is within the ESP32 GPIO rating. Use a transistor driver if required. Never apply 5 V logic to ESP32 GPIO pins.
