# Wiring and Connections

| Module pin | ESP32 connection | Notes |
|---|---|---|
| DS18B20 VDD (red) | 3V3 | Sensor supply |
| DS18B20 GND (black) | GND | Common ground |
| DS18B20 DATA (yellow) | GPIO 4 | OneWire data; pull up to 3.3 V |
| LCD SDA | GPIO 21 | I2C data |
| LCD SCL | GPIO 22 | I2C clock |
| LCD VCC | 5V/VIN | Confirm backpack logic compatibility |
| LCD GND | GND | Common ground |
| Buzzer signal | GPIO 18 | Check module current/voltage |
| Buzzer GND | GND | Common ground |
| Buzzer VCC | Suitable module supply | Follow module rating |

## DS18B20 pull-up
Connect GPIO 4 data to 3.3 V through a pull-up resistor. The prototype record used 1 kΩ after 47 Ω did not work. A 4.7 kΩ resistor is the conventional value to test. Verify wiring and sensor lead identification before powering.

## Network
The firmware uses Wi-Fi station mode and joins an existing router/mobile hotspot; it does not create its own access point. The browser device must be on the same network. Find the ESP32 IP in Serial Monitor at 115200 baud.
