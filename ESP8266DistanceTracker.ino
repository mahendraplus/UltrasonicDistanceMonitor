#include <Servo.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncWebServer.h>

Servo myservo;
int trigPin = D1;  // Define the trigger pin
int echoPin = D2;  // Define the echo pin
long duration;
int distance;

// Replace with your desired SSID and password for the ESP8266's AP mode
const char* apSsid = "MAX-PROJECT_ig-@m4u.xt";
const char* apPassword = "11223344";

AsyncWebServer server(80);

void setup() {
  Serial.begin(9600);
  myservo.attach(D4);  // Attach the servo to D4 pin
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set ESP8266 as an Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(apSsid, apPassword);

  // Serve the web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    String html = "<html><head><style>body{background-color:black;color:green;}</style></head><body>";
    html += "<h1>Distance Sensor Data</h1>";
    html += "<p>Distance: <span id='distance'></span> cm</p>";
    html += "<p>&copy; 2023 GitHub.com/mahendraplus - Mahendra Mali (MAX)</p>"; // Copyright notice
    html += "<script>setInterval(function() { fetch('/data').then(response => response.json()).then(data => document.getElementById('distance').textContent = data.distance + ' cm'); }, 1000);</script>";
    html += "</body></html>";
    request->send(200, "text/html", html);
  });

  // Serve JSON data
  server.on("/data", HTTP_GET, [](AsyncWebServerRequest *request){
    String json = "{\"distance\": " + String(distance) + "}";
    request->send(200, "application/json", json);
  });

  // Start server
  server.begin();
}

void loop() {
  // Send a short pulse to trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the duration of the echo pulse
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if an object is within a certain range (adjust the threshold as needed)
  if (distance < 20) {
    // Object detected, move the servo to 90 degrees
    myservo.write(180);
    delay(100); // Wait for stability
  } else {
    // No object detected, move the servo to 0 degrees
    myservo.write(0);
    delay(100); // Wait for stability
  }
}
