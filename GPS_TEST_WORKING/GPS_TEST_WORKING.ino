#include <TinyGPS++.h>
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in User_Setup.h

TinyGPSPlus gps;  // the TinyGPS++ object


//SET GLOBAL VARIABLES & DATA
const double TREASURE_LAT = 37.46120465557255;
const double TREASURE_LNG = -122.43577242318591;

const int buttonPin_1 = 0; 
const int buttonPin_2 = 35; 

// int buttonState_1 = LOW; 
// int buttonState_2 = LOW; 

int button_1_lastState = LOW; 
int button_1_currentState;  

int button_2_lastState = LOW; 
int button_2_currentState;  


void setup() {
  //SETUP BUTTONS
  pinMode(buttonPin_1, INPUT_PULLUP);
  pinMode(buttonPin_2, INPUT_PULLUP);

  //SET UP SCREEN
  tft.init();
  tft.setRotation(0);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(1);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);

  // DRAW CLOCK THING (x, y, radius, color)

  tft.fillCircle(64, 64, 61, TFT_BLUE);
  tft.fillCircle(64, 64, 57, TFT_BLACK);

  //SETUP SERIAL FOR GPS
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, 26, 25); //26 is TX , 25 is RX 
  Serial.println(F("ESP32 - GPS module"));
}

void loop() {

  if (Serial2.available() > 0) {
    if (gps.encode(Serial2.read())) {
      if (gps.location.isValid()) {

        //BUTTON STUFF
        button_1_currentState = digitalRead(buttonPin_1);
        button_2_currentState = digitalRead(buttonPin_2);

        //TREASURE LOCATION
        double distanceTo =
          gps.distanceBetween(
            gps.location.lat(),
            gps.location.lng(),
            TREASURE_LAT,
            // TREASURE_LNG) / 1000.0;
            TREASURE_LNG);

        double courseTo =
          gps.courseTo(
            gps.location.lat(),
            gps.location.lng(),
            TREASURE_LAT,
            TREASURE_LNG);

          
          tft.fillCircle(64, 64, 57, TFT_BLACK); // clear circle


          tft.drawLine(57*cos(courseTo), 57*sin(courseTo), 64, 64, TFT_RED);



          String distanceToDestination = String(distanceTo);
          tft.setTextColor(TFT_GREEN, TFT_BLACK);
          tft.drawString("Distance:", 0, 130, 4);
          tft.setTextColor(TFT_WHITE, TFT_BLACK);
          tft.drawString(distanceToDestination, 0, 160, 4);

          // String courseToDestination = String(courseTo);
          // tft.drawString("Course to Treasue:", 0, 60, 4);
          // tft.drawString(courseToDestination, 0, 90, 4);
          tft.setTextColor(TFT_GREEN, TFT_BLACK);
          tft.drawString("Course:", 0, 190, 4);
          tft.setTextColor(TFT_WHITE, TFT_BLACK);
          String courseToDestination = String(courseTo);
          tft.drawString(courseToDestination, 0, 220, 4);


        


        // // HANDLE BUTTON 1
        // if(button_1_lastState == HIGH && button_1_currentState == LOW){

        //   tft.fillScreen(TFT_BLACK);
        //   // DISPLAY LATITUDE ON SCREEN
        //   String gpsLat = String(gps.location.lat());
        //   tft.drawString("Lat:     " + gpsLat, 0, 0, 4);
        //   // DISPLAY LONGITUDE ON SCREEN
        //   String gpsLong = String(gps.location.lng());
        //   tft.drawString("Long:     " + gpsLong, 0, 30, 4);
        //   // DISPLAY SATELLITES ON SCREEN
        //   String gpsSats = String(gps.satellites.value());
        //   tft.drawString("Sat_Count:     " + gpsSats, 0, 60, 4); 

        //   if (gps.speed.isValid()) {
        //     //DISPLAY ALTITUDE ON SCREEN
        //     String gpsSpeed = String(gps.speed.mph());
        //     tft.drawString("Speed:     " + gpsSpeed, 0, 90, 4); 
        //   } else {
        //     tft.drawString("Speed: Invalid", 0, 90, 4);
        //   } 

        //   // DISPLAY LATITUDE ON SCREEN
        //   // String gpsLat = String(gps.location.lat());
        //   // tft.drawString("Lat:     " + gpsLat, 0, 0, 4);

        // //    Serial.print("Distance (km) to Eiffel Tower: ");
        // // Serial.println(distanceKm);
        // // Serial.print("Course to Eiffel Tower: ");
        // // Serial.println(courseTo);
        // // Serial.print("Human directions: ");
        // // Serial.println(gps.cardinal(courseTo));



        // }
        // else if(button_1_lastState == LOW && button_1_currentState == HIGH){
        //   tft.fillScreen(TFT_BLACK); //clear screen
        //   tft.setTextColor(TFT_GREEN, TFT_BLACK); // set initial text color

        //   String distanceToDestination = String(distanceKm);
        //   tft.drawString("Distance to Treasure:", 0, 0, 4);
        //   tft.setTextColor(TFT_WHITE, TFT_BLACK);
        //   tft.drawString(distanceToDestination, 0, 30, 4);

        //   // String courseToDestination = String(courseTo);
        //   // tft.drawString("Course to Treasue:", 0, 60, 4);
        //   // tft.drawString(courseToDestination, 0, 90, 4);
        //   tft.setTextColor(TFT_GREEN, TFT_BLACK);
        //   tft.drawString("Course to Treasue:", 0, 60, 4);
        //   tft.setTextColor(TFT_WHITE, TFT_BLACK);
        //   tft.drawString(gps.cardinal(courseTo), 0, 90, 4);

        // }

        // // save the the last state
        // button_1_lastState = button_1_currentState;

        // //HANDLE BUTTON 2
        // if(button_2_lastState == HIGH && button_2_currentState == LOW)
        //   tft.setTextColor(TFT_CYAN, TFT_BLACK);

        // else if(button_2_lastState == LOW && button_2_currentState == HIGH)
        //   tft.setTextColor(TFT_GREEN, TFT_BLACK);

        // // save the the last state
        // button_2_lastState = button_2_currentState;



        // LOG LATITUDE
        Serial.print(F("- latitude: "));
        Serial.println(gps.location.lat());

        //LOG LONGITUDE
        Serial.print(F("- longitude: "));
        Serial.println(gps.location.lng());
        
        // LOG NUMBER OF SATELLITES
        Serial.print(F("- SATELLITES: "));
        Serial.print(gps.satellites.value()); 
        

// TESTINNNNNGG

        
        Serial.print("Distance to Treasure: ");
        Serial.println(distanceTo);
        Serial.print("Course to Treasure: ");
        Serial.println(courseTo);
        Serial.print("Human directions: ");
        Serial.println(gps.cardinal(courseTo));



// END TESTINGGGGG


        //LOG ALTITUDE
        if (gps.altitude.isValid()){
          // LOG ALTITUDE
          Serial.print(F("- altitude: "));
          Serial.println(gps.altitude.feet());
          Serial.println(F(" feet"));
        }else{
          Serial.println(F("INVALID"));
        }

      } else {
        Serial.println(F("- location: INVALID"));
      }

      // LOG SPEED
      Serial.print(F("- speed: "));
      if (gps.speed.isValid()) {
        Serial.print(gps.speed.mph());
        Serial.println(F(" mph"));
      } else {
        Serial.println(F("INVALID"));
      }

      Serial.println();
    }
  }else{
    Serial.println(F("NOT WORKING"));
    // tft.drawString("NOT WORKING", 0, 0, 4);
  }

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

