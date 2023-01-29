

/* Luis Medina
Control of an LED strip using ESP8266 and a logic-level MOSFET
Instructions will be made available on https://wwww.makerluis.com

Credits to original code: Aruna Tennakoon (https://github.com/kakopappa)
Source: https://github.com/kakopappa/arduino-esp8266-alexa-multiple-wemo-switch */



#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h" 

// MOSFET PIN
/* Use this pin to drive a Logic-level MOSFET. Recommended: RFP30N06LE, 80N06L
The MOSFET will be used to open/shot the ground wire from the LED to turn it
ON or OFF based on the logic state of this pin*/
const int relay = 0; // Wemos D1 mini Pin D3

// prototypes
boolean connectWifi();

//on/off callbacks
bool LEDon();
bool LEDoff();

// Change this before you flash
const char* ssid = "yourSSID";
const char* password = "yourPASSWORD";

boolean wifiConnected = false;

UpnpBroadcastResponder upnpBroadcastResponder;

Switch *LED = NULL;

bool isLEDon = false;

void setup()
{
  Serial.begin(9600);

  // Configure relay pin to digital output
  pinMode(relay, OUTPUT);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected) {
    upnpBroadcastResponder.beginUdpMulticast();

    // Define your switches here. Max 10
    // Format: Alexa invocation name, local port no, on callback, off callback
    LED = new Switch("LED cuarto", 82, LEDon, LEDoff);

    Serial.println("Adding switches upnp broadcast responder");
    upnpBroadcastResponder.addDevice(*LED);
  }
}

void loop()
{
  if (wifiConnected) {
    upnpBroadcastResponder.serverLoop();

    LED->serverLoop();
  }
}

bool LEDon() {

  digitalWrite(relay, HIGH);
  Serial.println("Switch 1 turn on ...");
  isLEDon = true;
  return isLEDon;
}

bool LEDoff() {
  digitalWrite(relay, LOW);
  Serial.println("Switch 1 turn off ...");
  isLEDon = false;
  return isLEDon;
}


// connect to wifi – returns true if successful or false if not
boolean connectWifi() {
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 10) {
      state = false;
      break;
    }
    i++;
  }

  if (state) {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("");
    Serial.println("Connection failed.");
  }

  return state;
}
