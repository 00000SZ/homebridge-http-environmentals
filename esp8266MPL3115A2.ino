#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include <SparkFunMPL3115A2.h>

// Wireless Configuration
#define WIFI_SSID "Wireless AP Name"
#define WIFI_PASSWORD "Wireless Passphrase"

// Webserver init
ESP8266WebServer server(80);

//Create an instance of the object
MPL3115A2 myPressure;

float pressure;
float temperature;

// Define webserver root
void handleRoot() {
  server.send(200, "text/plain", "/sensors - JSON output of attached sensor data");
}
// function to handle any page that the webserver doesn't offer, resulting in a 404
// again not needed, but nice to have
void handleNotFound() {
  server.send(404, "text/plain", "404 Not Found.");
}

void setup() {

  // set the baud rate to 9600
  Serial.begin(9600); // Start serial output

  // if the SSID saved does not match the one stored in NVRAM, connect to new SSID
  if (WiFi.SSID() != WIFI_SSID) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  } else {
    Serial.println("Previous Wifi credientials found!");
  }

  Wire.begin();        // Join i2c bus

  // Sensor init
  myPressure.begin(); // Get sensor online
  myPressure.setModeBarometer(); // Set sensor to barometer mode
  myPressure.setOversampleRate(7); // Set Oversample to the recommended 128
  myPressure.enableEventFlags(); // Enable all three pressure and temp event flags

  // Serial init
  Serial.begin(9600);

  // Wifi init
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // once connected, print SSID, and IP address of this device
  Serial.println("Connected to: " + String(WIFI_SSID));
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // defining the root of the webserver
  server.on("/", handleRoot);

  // setup the page
  server.on("/sensors", []() {

    // Get values
    temperature = myPressure.readTemp();
    pressure = myPressure.readPressure() /100; // Convert pascals to hectopascal (hPa)

    // Create a char to
    char json[128];
    snprintf(json, sizeof(json), "{\n \"temperature\":%i,\n \"humidity\":%i,\n \"pressure\":%i\n }", round(temperature), 67, round(pressure));

    // Print some debug to serial
    Serial.println("Homebridge request received.....");
    Serial.print("Temp(c): ");
    Serial.print(temperature);
    Serial.println();
    Serial.print("Pressure(hPa): ");
    Serial.print(pressure);
    Serial.println();

    // Send JSON response
    server.send(200, "application/json", json);
  });

  // this calls the handleNotFound() function - if a page that isn't found is accessed
  server.onNotFound(handleNotFound);

  // Start the web server
  server.begin();
}

// Main loop
void loop() {
  server.handleClient();
  delay(500);
}
