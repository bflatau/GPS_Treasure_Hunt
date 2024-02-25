/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-gps
 */

// GPS REFERENCE: http://arduiniana.org/libraries/tinygpsplus/

// USING TTGO-LoRa32_V2 BOARD

#include <TinyGPS++.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

TinyGPSPlus gps;  // the TinyGPS++ object



void setup() {

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 26, 25); //25 is RX (Black), 26 is TX (Yellow)

  Serial.println(F("ESP32 - GPS module"));
}

void loop() {
  if (Serial2.available() > 0) {
    if (gps.encode(Serial2.read())) {
      if (gps.location.isValid()) {
        // LOG LATITUDE
        Serial.print(F("- latitude: "));
        Serial.println(gps.location.lat());

        // DISPLAY LATITUDE ON SCREEN
        String gpsLat = String(gps.location.lat());
        tft.drawString("Lat:     " + gpsLat, 0, 0, 4);

        //LOG LONGITUDE
        Serial.print(F("- longitude: "));
        Serial.println(gps.location.lng());
        
        // DISPLAY LONGITUDE ON SCREEN
        String gpsLong = String(gps.location.lng());
        tft.drawString("Long:     " + gpsLong, 0, 30, 4);

        // LOG NUMBER OF SATELLITES
        Serial.print(F("- SATELLITES: "));
        Serial.print(gps.satellites.value()); 
        String gpsSats = String(gps.satellites.value());
        tft.drawString("Sat_Count:     " + gpsSats, 0, 60, 4); 

        //CHECK IF ALTITUDE IS VALID
        if (gps.altitude.isValid()){
          // LOG ALTITUDE
          Serial.print(F("- altitude: "));
          Serial.println(gps.altitude.feet());
          Serial.println(F(" feet"));
          //DISPLAY ALTITUDE ON SCREEN
          String gpsAlt = String(gps.altitude.feet());
          tft.drawString("Alt:     " + gpsAlt, 0, 90, 4); 
        }else{
          Serial.println(F("INVALID"));
        }

      } else {
        Serial.println(F("- location: INVALID"));
      }

      Serial.print(F("- speed: "));
      if (gps.speed.isValid()) {
        Serial.print(gps.speed.mph());
        Serial.println(F(" mph"));
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.println();
    }
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}







//      Serial.print(F("- GPS date&time: "));
//      if (gps.date.isValid() && gps.time.isValid()) {
//        Serial.print(gps.date.year());
//        Serial.print(F("-"));
//        Serial.print(gps.date.month());
//        Serial.print(F("-"));
//        Serial.print(gps.date.day());
//        Serial.print(F(" "));
//        Serial.print(gps.time.hour());
//        Serial.print(F(":"));
//        Serial.print(gps.time.minute());
//        Serial.print(F(":"));
//        Serial.println(gps.time.second());
//      } else {
//        Serial.println(F("INVALID"));
//      }
