# Implementation of Alexa Voice Control for an LED strip using ESP8266 (Wemos D1 mini)

### Forked from [original repository by Aruna Tennakoon](https://github.com/kakopappa/arduino-esp8266-alexa-multiple-wemo-switch)

This project supports turning on/off an LED strip through Alexa Voice commands using 1 ESP-8266 board.

Parts you need:

WeMos D1-mini ($4.00). [You can buy if from Aliexpress](http://www.aliexpress.com/store/product/D1-mini-Mini-NodeMcu-4M-bytes-Lua-WIFI-Internet-of-Things-development-board-based-ESP8266/1331105_32529101036.html)

Logic-level MOSFET. Recommended: RFP30N06LE, 80N06L

Toggle switch

Optional: 
Resistor (any value between 1k and 100k). Used in case your LED remains ON after you have switched the power off. This is due to the residual capacitance of the MOSFET which is some cases is high enough to keep the LED on.

Schematic diagram:
![Schematic diagram of LED Strip connected to ESP8266 with MOSFET control and toggle switch](Schematic_ESP8266_LED_Strip_MOSFET.JPG?raw=true "Schematic ESP8266 LED Strip MOSFET")