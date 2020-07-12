#include <ESP8266WiFi.h>                                                // esp8266 library
#include <FirebaseArduino.h>                                             // firebase library

#define FIREBASE_HOST "lock-xx.firebaseio.com"                         // the project name address from firebase id
#define FIREBASE_AUTH "TPYxoqP6NhxxxxxxxHhAkoSkjiJSHgprF2SxgzSH5"                    // the secret key generated from firebase
#define WIFI_SSID "a"                                          // input your home or public wifi name 
#define WIFI_PASSWORD "password "  //password of wifi ssid
#define LOCK 2

String fireStatus = "";                                                     // led status received from firebase                                                              // for external led
void setup() {
  Serial.begin(9600);
  delay(1000);   
  pinMode(LOCK, OUTPUT);                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                      //try to connect with wifi
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
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
}

void loop() {
  fireStatus = Firebase.getString("Status");                                      // get ld status input from firebase
  if (fireStatus == "\"UNLOCKED\"") {                                                          // compare the input of led status received from firebase
    Serial.println("Unlocking");                                                                          // make bultin led ON
    digitalWrite(LOCK, HIGH);                                                        // make external led ON
  } 
  else if (fireStatus =="\"LOCKED\"") {                                                  // compare the input of led status received from firebase
    Serial.println("Locking");                                           
    digitalWrite(LOCK, LOW);                                                         // make external led OFF
  }
  else {
    Serial.println("Wrong Credentials!");
  }
}