#include <WiFi.h> //Library for wirless shield sensor
#include <PubSubClient.h> //Library for serial connection to the GPS device
#include <TinyGPS++.h> //Library for GPS device
#include <SoftwareSerial.h> //Library for GPS device


/*
================================================================================
Standard attribute station components
================================================================================
*/
static const int RXPin = 4, TXPin = 6; //RXP GPS device pin and TXP GPS device pin
static const uint32_t GPSBaud = 9600; //Serial GPS device port


/*
================================================================================
Shield Wifi
================================================================================
*/
char ssid[] = "C5ADB0";  //"WiFi-Arnet-eh88";      // your network SSID (name) 
char pass[] = "101090524"; //"vjs5nt2m";             // your network (password)
int status = WL_IDLE_STATUS;          // the Wifi radio's status


/*
================================================================================
MQTT Client
================================================================================
*/
const char* mqttServer = "soldier.cloudmqtt.com";   // the URL mqtt server
const int   mqttPort = 16402;                       // the por of comunnication
const char* mqttUser = "fvdkrfcz";                  // your usser mqtt client
const char* mqttPassword = "u-wUVsT3k9WQ";          // your password mqtt client


/*
================================================================================
Objects initializations
================================================================================
*/
TinyGPSPlus gps; //The TinyGPS++ object
SoftwareSerial ss(RXPin, TXPin); //The serial connection to the GPS device
WiFiClient shieldWiFiClient;
PubSubClient client(shieldWiFiClient);


void setup() {
  
  Serial.begin(9600);
  ss.begin(GPSBaud);  
  
}

void loop() {  

  if (status != WL_CONNECTED)
    connectShieldToWiFi();
    
  if (!client.connected())
    reconnectMqttClient();

  else {
    client.loop();
    sendDataTo("/sm/station1/variables"); //To publish data
    delay(10000);
  }

  
}


void connectShieldToWiFi() {
  /*
   * 
   */

  // attempt to connect using WPA encryption:
  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(ssid, pass);

  // if you're not connected, stop here:
  if ( status != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    while(true);
  }
  // if you are connected, print out info about the connection:
  else {
    Serial.println("Connected to network: ");
    Serial.println(ssid);
    Serial.println("...connected!!");
  }
  
}


void reconnectMqttClient() {
  /*
   * 
   */

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  
  Serial.println("Connecting to MQTT: ");
  Serial.println(mqttServer);

  if (client.connect("ArduinoShield", mqttUser, mqttPassword )) {
    Serial.println("...connected!!");  
  } else {
    Serial.println("Failed with state");
    delay(2000);
  }
  
  //Suscriptions
  client.subscribe("/sm/+/variables");
  
}


void callback(String topic, byte* payload, unsigned int length) {
  String message_received = "";
  
  for (int p = 0; p < length; p++) {
    message_received += (char)payload[p];
  }
  message_received.toUpperCase();
  
  Serial.println("Message received: ");
  Serial.print(message_received);
  
  //Publishing
  if (message_received == "foo") {
    // doSomething().. 
  }
  
}


void sendDataTo(String topic) {
  char data[500];
  sprintf(data, "{%d, %d, %d, %d, %d, %d, %d, %s, %s}", char(100), char(200), char(300), char(400), char(500), char(600), char(700));

  Serial.println(sizeof(data));
  Serial.println(data);
  
  if (topic == "/sm/station1/variables")  {
    Serial.println("¿Posted message? : ");
    Serial.print(client.publish("/sm/station1/variables", data)); }

}
