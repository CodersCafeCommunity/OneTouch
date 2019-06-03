#include <ESP8266WiFi.h>                                                  // ESP8266 library
#include <FirebaseArduino.h>                                              // Firebase library

#define FIREBASE_HOST "lock-b2a19.firebaseio.com"                         // Firebase URL
#define FIREBASE_AUTH "TPYxoqP6NhSHkpaXHhAkoSkjiJSHgprF2SxgzSH5"          // The secret key generated from firebase
#define WIFI_SSID "a"                                                     // Input your  wifi name 
#define WIFI_PASSWORD "password "                                         // Password of wifi 
#define LOCK 2

String fireStatus = "";                                                                                                                   
void setup() {
  Serial.begin(9600);
  delay(1000);   
  pinMode(LOCK, OUTPUT);                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                    
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       
}

void loop() {
  fireStatus = Firebase.getString("Status");                               // Get lock status input from firebase
  if (fireStatus == "\"UNLOCKED\"") {                                      // Compare the input of lock status received from firebase
    Serial.println("Unlocking");                                                                          
    digitalWrite(LOCK, HIGH);                                              // Unlocking
  } 
  else if (fireStatus =="\"LOCKED\"") {                                                  
    Serial.println("Locking");                                           
    digitalWrite(LOCK, LOW);                                               // Locking
  }
  else {
    Serial.println("Wrong Credentials!");
  }
}
