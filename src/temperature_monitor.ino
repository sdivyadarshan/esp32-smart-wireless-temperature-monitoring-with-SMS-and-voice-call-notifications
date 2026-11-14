#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Replace placeholders locally. Never commit real credentials.
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* TWILIO_URL = "https://YOUR-TWILIO-FUNCTION-URL";

#define ONE_WIRE_BUS 4
#define BUZZER_PIN 18
const float MIN_THRESHOLD = -55.0;
const float MAX_THRESHOLD = 125.0;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
LiquidCrystal_I2C lcd(0x27, 16, 2);
WebServer server(80);

float currentTemp = DEVICE_DISCONNECTED_C;
float threshold = 35.0;
bool alertSent = false;
unsigned long lastSample = 0;
const unsigned long SAMPLE_INTERVAL = 1000;

bool sendAlert() {
  if (WiFi.status() != WL_CONNECTED) return false;
  WiFiClientSecure client;
  // Prototype shortcut only: disables TLS certificate verification.
  // Replace with trusted CA certificate validation before deployment.
  client.setInsecure();
  HTTPClient https;
  if (!https.begin(client, TWILIO_URL)) return false;
  https.setTimeout(10000);
  int code = https.GET();
  Serial.printf("Twilio Function HTTP code: %d\n", code);
  Serial.println(https.getString());
  https.end();
  return code >= 200 && code < 300;
}

void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  if (currentTemp == DEVICE_DISCONNECTED_C) lcd.print(" SENSOR ERR");
  else { lcd.print(currentTemp, 1); lcd.print((char)223); lcd.print("C"); }
  lcd.setCursor(0, 1);
  lcd.print("Limit:");
  lcd.print(threshold, 1);
  lcd.print((char)223);
  lcd.print("C");
}

void handleAlert() {
  if (currentTemp == DEVICE_DISCONNECTED_C) {
    digitalWrite(BUZZER_PIN, LOW);
    return;
  }
  if (currentTemp > threshold) {
    digitalWrite(BUZZER_PIN, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0); lcd.print("HIGH TEMP ALERT");
    lcd.setCursor(0, 1); lcd.print(currentTemp, 1); lcd.print((char)223); lcd.print("C");
    if (!alertSent) {
      alertSent = sendAlert();
      if (!alertSent) Serial.println("Cloud alert failed; retrying next sample");
    }
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    alertSent = false;
  }
}

void handleRoot() {
  String page = R"rawliteral(
<!doctype html><html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<meta http-equiv="refresh" content="5"><title>ESP32 Temperature Monitor</title>
<style>
body{font-family:Arial;background:#101827;color:#eef2ff;padding:24px}
main{max-width:620px;margin:auto;background:#1d293b;padding:24px;border-radius:16px}
.value{font-size:2.2rem;font-weight:bold}form{display:flex;gap:10px;flex-wrap:wrap;margin-top:20px}
input,button{font-size:1rem;padding:12px;border:0;border-radius:8px}
button{background:#38bdf8;color:#082f49;font-weight:bold}small{color:#aab8cc}
</style></head><body><main><h1>ESP32 Smart Temperature Monitor</h1>
<p>Current temperature</p><div class="value">)rawliteral";
  if (currentTemp == DEVICE_DISCONNECTED_C) page += "Sensor error";
  else page += String(currentTemp, 1) + " &deg;C";
  page += R"rawliteral(</div><p>Configured threshold: <b>)rawliteral";
  page += String(threshold, 1);
  page += R"rawliteral( &deg;C</b></p>
<form action="/set" method="get"><label for="th">New threshold (&deg;C)</label>
<input id="th" type="number" step="0.1" min="-55" max="125" name="th" required>
<button type="submit">Update threshold</button></form>
<p><small>Refreshes every 5 seconds. Use the same Wi-Fi network.</small></p>
</main></body></html>)rawliteral";
  server.send(200, "text/html", page);
}

void handleSet() {
  if (!server.hasArg("th")) { server.send(400, "text/plain", "Missing threshold"); return; }
  String raw = server.arg("th");
  char* endPtr = nullptr;
  float value = strtof(raw.c_str(), &endPtr);
  if (endPtr == raw.c_str() || *endPtr != '\0' || !isfinite(value) ||
      value < MIN_THRESHOLD || value > MAX_THRESHOLD) {
    server.send(400, "text/plain", "Threshold must be numeric and between -55 and 125 C");
    return;
  }
  threshold = value;
  alertSent = false;
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  Wire.begin(21, 22);
  lcd.init(); lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("Connecting WiFi");
  sensors.begin();
  sensors.setResolution(12);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }
  Serial.println("\nWi-Fi connected");
  Serial.print("Dashboard IP: "); Serial.println(WiFi.localIP());
  lcd.clear(); lcd.print("WiFi connected");
  lcd.setCursor(0, 1); lcd.print(WiFi.localIP());
  delay(2500);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/set", HTTP_GET, handleSet);
  server.begin();
}

void loop() {
  server.handleClient();
  if (millis() - lastSample >= SAMPLE_INTERVAL) {
    lastSample = millis();
    sensors.requestTemperatures();
    currentTemp = sensors.getTempCByIndex(0);
    Serial.print("Temperature: ");
    if (currentTemp == DEVICE_DISCONNECTED_C) Serial.println("Sensor error");
    else { Serial.print(currentTemp, 2); Serial.println(" C"); }
    updateLCD();
    handleAlert();
  }
}
