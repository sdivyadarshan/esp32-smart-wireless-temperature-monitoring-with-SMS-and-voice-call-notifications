# Twilio Notification Integration

## Architecture
The ESP32 does not directly send SMS or place a call. On threshold crossing, it requests a Twilio-hosted Function over HTTPS. The Function uses Twilio cloud services to send the SMS and initiate the automated voice call.

## Setup outline
1. Configure the Function and its SMS/voice workflow in your Twilio account.
2. Store Twilio credentials in protected Function environment/configuration variables.
3. Configure authorized sender/recipient numbers in the cloud Function.
4. Add request authentication/shared-secret validation and rate limiting.
5. Configure the Function endpoint in the local firmware build.
6. Test using an authorized recipient and verify both message and call delivery.

## Security
- Never commit Wi-Fi passwords, Twilio Auth Token, Account SID, private phone numbers or request secrets.
- Rotate any Auth Token previously exposed in a screenshot, chat or repository.
- A publicly callable unauthenticated endpoint can be abused and may incur charges.
- Keep secrets in local-only configuration or protected cloud environment variables.

## TLS caveat
The prototype calls WiFiClientSecure::setInsecure(), which skips server certificate verification. Replace this with trusted certificate validation before production deployment.

## Verification
Test the cloud Function independently, then test the ESP32 request. Check HTTP status and Function logs; redact all personal/account information in evidence.
