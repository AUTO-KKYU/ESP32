#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char *ssid = "AIE_509_2.4G";
const char *password = "addinedu_class1";
const int ledPin = 23;

AsyncWebServer server(80);

const char html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<body>
<center>
<h1>Hello, ESP32 Web Server- Async</h1>
<div>LED PIN 23 :
<input type="checkbox" onchange="toggleCheckBox(this)" />
</div>
<script>
function toggleCheckBox(element) {
  var request new XMLHttpRequest();
  if (element.checked)
  {
    request.open("GET", "/on", true);
  }
  else
  {
    request.open("GET", "/off", true);
  }
  request.send();
}
</script>
</center>
</body>
</html>
)rawliteral";

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("ESP32 Web Server Start");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nIP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", html);
  });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);
    request->send_P(200, "text/html", html);
  });

  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);
    request->send_P(200, "text/html", html);
  });

  server.begin();
  Serial.println("HTTP Server Started!");
}

void loop() {
  // loop body can be empty in case of AsyncWebServer
  // server.handleClient();
}
