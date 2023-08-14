#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <SPIFFS.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "display_weather_on_oled.h"


float temperature;
float pressure;
float humidity;
String ip;

Adafruit_BME280 bme; // I2C


// My network credentials
const char* ssid = "StarLink";
const char* password = "admin123";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readBME280Temperature() {
  float t = bme.readTemperature(); //readin temperature
  temperature = t;
  //t = 1.8 * t + 32; //temp to Fahrenheit
  if (isnan(t)) {
    Serial.println("Failed to read from BME280 sensor!");
    return "";
  }
  else {
    Serial.println(t);
    return String(t);
  }
}

String readBME280Humidity() {
  float h = bme.readHumidity(); //reading humidity
  humidity = h;
  if (isnan(h)) {
    Serial.println("Failed to read from BME280 sensor!");
    return "";
  }
  else {
    Serial.println(h);
    return String(h);
  }
}

String readBME280Pressure() {
  float p = bme.readPressure() / 100.0F;
  pressure = p;
  if (isnan(p)) {
    Serial.println("Failed to read from BME280 sensor!");
    return "";
  }
  else {
    Serial.println(p);
    return String(p);
  }
}

void setup() {
  display_weather_on_oled_setup();
  display.println("Loading...");

  Serial.begin(115200); // Serial port for debugging purposes

  bool status;
  // default settings
  // (you can also pass in a Wire library object like &Wire2)
  status = bme.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  }

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());
  //display.println(WiFi.localIP();

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/index.html");
  });

   server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/automation.html");
  });
    server.on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send(SPIFFS, "/weatherStation.html");
  });


  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", readBME280Temperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", readBME280Humidity().c_str());
  });
  server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->send_P(200, "text/plain", readBME280Pressure().c_str());
  });



  // Start server
  server.begin();

}

void loop() {
  display_weather_on_oled();
}

void display_weather_on_oled() {
  display.clearDisplay();
  display.setCursor(10, 5);
  display.println("*Weather Station*");
  display.println("------------------");

  //temperature
  display.print("Temp    : ");
  display.print(temperature);
  display.println("*C");

  //pressure
  display.print("Press   : ");
  display.print(pressure);
  display.println(" hPa");

  //Humidity
  display.print("Humidity: ");
  display.print(humidity);
  display.println(" %");

  //LocalIp
  display.print("IP:");
  display.print("192.168.0.199");

  display.display();

  delay (1000);
}
