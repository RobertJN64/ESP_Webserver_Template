#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <AsyncJson.h>
#include <html.hpp>
#include <secrets.h>
#include <WiFi.h>

#define HTML_HEADER "ESP32 Webserver"
#define LED_PIN 2 //built in LED
unsigned long blink_led_end_time = 0;

StaticJsonDocument<65536> saved_json;
const char starting_json[] PROGMEM = R"rawliteral(
{
  "Example Item": {"option": "C", "text": "Example text"},
  "Another Item": {"option": "A", "text": "More text"}
}
)rawliteral";

#pragma region Webserver
AsyncWebServer server(80);

String processor(const String& var)
{
  if (var == "HEADER") {
    return HTML_HEADER;
  }
  return "";
}

void start_webserver() {
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/stylesheet", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/css", stylesheet_css);
  });

  server.on("/second_page", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", second_page_html, processor);
  });

  server.on("/blink_led", HTTP_GET, [] (AsyncWebServerRequest *request) {
    blink_led_end_time = millis() + 5000;
    request->send(200, "text/plain", "OK");    
  });

  server.on("/get_json", HTTP_GET, [](AsyncWebServerRequest *request) {
    String config;
    serializeJson(saved_json, config);
    request->send(200, "text/plain", config);
  });

  AsyncCallbackJsonWebHandler* d_handler = new AsyncCallbackJsonWebHandler("/set_json", [](AsyncWebServerRequest *request, JsonVariant &json) {
    String jsonstr;
    serializeJsonPretty(json, jsonstr);
    Serial.println("Recieved json: ");
    Serial.println(jsonstr);
    
    deserializeJson(saved_json, jsonstr);
    request->send(200, "text/plain", "OK");
  }, 65536);
  server.addHandler(d_handler);
  server.begin();
}
#pragma endregion

bool connect_to_wifi() {
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
  WiFi.begin(SSID, PASS);
  
  Serial.println("Connecting");
  unsigned long starttime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - starttime < 60000) { //connect for 1 min
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connection failed.");
    WiFi.disconnect();
    return false;
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  return true;
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.setDebugOutput(true);
  Serial.println("Serial connected!");

  pinMode(LED_PIN, OUTPUT);

  deserializeJson(saved_json, starting_json);

  if (connect_to_wifi()) {
    start_webserver();
  }
}

void loop() {
  if (millis() < blink_led_end_time) {
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
      delay(500);
  }
  delay(10);
}
