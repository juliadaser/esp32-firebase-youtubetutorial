/*
  Rui Santos
  Complete project details at our blog.
    - ESP32: https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
    - ESP8266: https://RandomNerdTutorials.com/esp8266-nodemcu-firebase-realtime-database/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/

// Importing libraries
#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

// Setting up your wifi connection
#define WIFI_SSID "PLACE_SSID_HERE"
#define WIFI_PASSWORD "PLACE_PASSWORD_HERE"

// Setting up Firebase
#define API_KEY ""
#define DATABASE_URL ""

// Setting up hardware components ( led & button )
#define ledPin 13
bool ledStatus = false;
#define buttonPin 12
int buttonState = 0;

//Define Firebase Data object and other silly things
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

void connectToWiFi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
    }
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  }

void setup(){  
  // setting Baud rate
  Serial.begin(115200);

  // setting the led pin as an output
  pinMode(ledPin, OUTPUT);

  // calling connectToWiFi function
  connectToWiFi();

  // Assigning the API key, and URL
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // Sign up
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  } else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop(){
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 100 || sendDataPrevMillis == 0)){}
    sendDataPrevMillis = millis();

    // reading the button state to see if it is pressed
    int buttonState = digitalRead(buttonPin);

    // sending the buttonState to the database so that pepis ESP turns on the LED whenever this button is pressed.
    if (Firebase.RTDB.setInt(&fbdo, "/julia_button_state", buttonState)){
      Serial.println("");
      Serial.println(buttonState);
      Serial.println("--- successfully saved to: " + fbdo.dataPath());
      Serial.println("(" + fbdo.dataType() + ")");
    }else {
      Serial.println("Data upload failed");
    }

    // we are then checking Pepis button state 
    if (Firebase.RTDB.getInt(&fbdo, "/pepi_button_state")){
      if(fbdo.dataType() == "int"){
        /* by setting the led status to pepis button state, we turn on the LED whenever Pepi 
        presses the button, and turn it off, whenever the button is released */
        ledStatus = fbdo.intData();
        digitalWrite(ledPin, ledStatus);
        Serial.println("Successful READ from" + fbdo.dataPath() + ": " + ledStatus + "!");
        }   
      } else {
        Serial.println("Data download failed");
    }
  }
