# Monitoring Algorithm

1. Initialize serial logging, buzzer, I2C LCD and DS18B20.
2. Join the configured Wi-Fi network in station mode.
3. Print the assigned local IP address.
4. Start the web server and register dashboard/threshold routes.
5. Service incoming browser requests continuously.
6. At the sampling interval, request and read a DS18B20 conversion.
7. If the sensor reading is invalid/disconnected, log the fault and do not evaluate a temperature alert.
8. Otherwise display the reading and compare it with the threshold.
9. If temperature is above threshold, activate the buzzer and request the Twilio Function once for the current event.
10. Mark the notification as sent only after a successful 2xx HTTP response; failed requests remain eligible for retry.
11. When temperature returns to or below threshold, turn off the buzzer and re-arm the next event.

## Threshold update
The browser submits a numeric value to /set. Firmware accepts values from -55 to 125 degrees C and rejects missing, non-numeric or out-of-range values with HTTP 400.

## Pseudocode
```text
initialize hardware; connect Wi-Fi; start web server
loop:
  service web requests
  when sample interval elapsed:
    read sensor
    if invalid: report sensor fault
    else:
      display reading
      if temperature > threshold:
        buzzer ON
        if event not yet notified: call cloud function
      else:
        buzzer OFF; re-arm notification
```

The current alert latch avoids repeated requests during one continuous above-threshold event. A production version should add retry backoff, cooldown and event logging.
