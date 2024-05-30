#include <ESP32Servo.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

const char *ssid = "AIE_509_2.4G";
const char *password = "addinedu_class1";

AsyncWebServer server(80);
Servo servo;
const int servo_pin = 5;

const char* INPUT_PARAM1 = "degree";

const char html[] PROGMEM = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <body>
  <center>
  <h1>Hello, ESP32 Web Server - Async</h1>
  <div>
  Photoresistor Value : <div id="sensor">None</div>
  </div>
  <form action="/get">
  Servo Degree : <input type="text" name="degree">
  <input type="submit" value="Submit">
  </form>
  <script>
    setInterval(getSensorValue, 1000); // 100ms was very frequent, changed to 1000ms
    function getSensorValue() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("sensor").innerHTML = this.responseText; 
        }
      };
      xhttp.open("GET", "/sensor", true);
      xhttp.send();
    }
  </script>
  </center>
  </body>
  </html>
)rawliteral";

String processor(const String& var) {
  Serial.println(var);
  return var;
}

void setup() {
  Serial.begin(115200);
  servo.attach(servo_pin); // Use variable instead of magic number
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
    request->send_P(200, "text/html", html, processor);
  });

  server.on("/sensor", HTTP_GET, [] (AsyncWebServerRequest *request) {
    int sensor = analogRead(34); // Ensure GPIO 34 is used and supports ADC
    String s1 = String(sensor);
    Serial.println(s1);
    request->send(200, "text/plain", s1);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage = request->getParam(INPUT_PARAM1)->value();
    Serial.println(inputMessage);
    float degree = inputMessage.toFloat();
    servo.write(degree);
    request->send_P(200, "text/html", html, processor);
  });

  server.begin();
  Serial.println("HTTP Server Started!");
  delay(100);
}

void loop() {
  // Simplified loop for demonstration
}
