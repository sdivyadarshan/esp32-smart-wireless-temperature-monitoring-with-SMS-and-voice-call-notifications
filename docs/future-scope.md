# Future Scope

Potential improvements; these are not claimed as implemented:
1. Replace setInsecure() with TLS certificate validation.
2. Authenticate dashboard users and protect threshold changes.
3. Add authentication and rate limiting to the Twilio Function.
4. Add sensor-disconnection alarm and recovery handling.
5. Implement notification cooldown, retry backoff and event logging.
6. Persist threshold configuration in non-volatile storage.
7. Use a non-blocking state machine or FreeRTOS tasks where justified.
8. Add watchdog, brownout and Wi-Fi reconnect handling.
9. Reduce LCD flicker with partial character updates.
10. Add automated tests for threshold parsing and alert-state transitions.
11. Measure power consumption and evaluate low-power operation.
12. Validate sensor accuracy against a trusted reference thermometer.
