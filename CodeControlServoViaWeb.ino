#include <WiFi.h>
#include <WebServer.h>
#include <ESP32Servo.h>

// Access Point Credentials
const char* ssid = "ESP32_Control";
const char* password = "12345678Password";

// Pin Configuration (WeMos D1 Mini ESP32)
const int SERVO_PIN = 18; // D18
const int GREEN_LED = 2;  // D2
const int RED_LED   = 4;  // D4

Servo myServo;
WebServer server(80);

// Styled HTML Web Interface
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Servo & Gate Control</title>
  <link href="https://fonts.googleapis.com/css2?family=Inter:wght@400;500;700&display=swap" rel="stylesheet">
  <style>
    * { box-sizing: border-box; margin: 0; padding: 0; font-family: 'Inter', sans-serif; }
    body { min-height: 100vh; display: flex; justify-content: center; align-items: center; background: linear-gradient(135deg, #0f172a 0%, #1e293b 100%); color: #f8fafc; padding: 20px; }
    .card { background: rgba(30, 41, 59, 0.7); backdrop-filter: blur(12px); border: 1px solid rgba(255, 255, 255, 0.1); border-radius: 24px; padding: 40px 30px; width: 100%; max-width: 420px; box-shadow: 0 20px 40px rgba(0, 0, 0, 0.3); text-align: center; }
    .card h2 { font-size: 1.6rem; font-weight: 700; margin-bottom: 8px; color: #ffffff; }
    .card p { font-size: 0.95rem; color: #94a3b8; margin-bottom: 32px; }
    .btn-group { display: flex; flex-direction: column; gap: 16px; }
    .btn { display: flex; align-items: center; justify-content: center; gap: 10px; width: 100%; padding: 16px; font-size: 1.1rem; font-weight: 700; border: none; border-radius: 14px; cursor: pointer; text-decoration: none; transition: all 0.25s ease; box-shadow: 0 4px 12px rgba(0, 0, 0, 0.15); }
    .btn-open { background: linear-gradient(135deg, #10b981 0%, #059669 100%); color: #ffffff; }
    .btn-open:hover { background: linear-gradient(135deg, #34d399 0%, #10b981 100%); transform: translateY(-2px); box-shadow: 0 8px 20px rgba(16, 185, 129, 0.35); }
    .btn-close { background: linear-gradient(135deg, #ef4444 0%, #dc2626 100%); color: #ffffff; }
    .btn-close:hover { background: linear-gradient(135deg, #f87171 0%, #ef4444 100%); transform: translateY(-2px); box-shadow: 0 8px 20px rgba(239, 68, 68, 0.35); }
    .btn:active { transform: translateY(0); }
  </style>
</head>
<body>
  <div class="card">
    <h2>Gate Control Panel</h2>
    <p>Select an action to control the servo motor and LEDs</p>
    <div class="btn-group">
      <a href="/open" class="btn btn-open"><span>Open</span></a>
      <a href="/close" class="btn btn-close"><span>Close</span></a>
    </div>
  </div>
</body>
</html>
)rawliteral";

  server.send(200, "text/html", html);
}

// Action: Open
void handleOpen() {
  myServo.write(90);             // Rotate Servo to 90 degrees
  digitalWrite(GREEN_LED, HIGH); // Turn ON Green LED
  digitalWrite(RED_LED, LOW);    // Turn OFF Red LED
  server.sendHeader("Location", "/");
  server.send(303);
}

// Action: Close
void handleClose() {
  myServo.write(0);              // Rotate Servo back to 0 degrees
  digitalWrite(GREEN_LED, LOW);  // Turn OFF Green LED
  digitalWrite(RED_LED, HIGH);   // Turn ON Red LED
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  // Configure LED Pins
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  
  // Initial state: Closed (Red LED ON)
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  // Attach and set Servo
  myServo.attach(SERVO_PIN);
  myServo.write(0);

  // Start Access Point
  WiFi.softAP(ssid, password);
  
  Serial.println("\n--- Access Point Started ---");
  Serial.print("SSID: ");
  Serial.println(ssid);
  Serial.print("Web Server IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Define Server Routes
  server.on("/", handleRoot);
  server.on("/open", handleOpen);
  server.on("/close", handleClose);

  server.begin();
}

void loop() {
  server.handleClient();
}