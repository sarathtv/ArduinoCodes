#include <ESP8266WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"

#define SECRET_SSID "Uptown"    // replace MySSID with your WiFi network name
#define SECRET_PASS "sarath5257"  // replace MyPassword with your WiFi password

#define SECRET_CH_ID 1672753      // replace 0000000 with your channel number
#define SECRET_WRITE_APIKEY "UI777588SR10RAOE"   // replace XYZ with your channel write API Key

#define DHTPIN 2     // D4 of nodemcu
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);
char ssid[] = SECRET_SSID;   // your network SSID (name) 
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

void setup() {
  Serial.begin(9600);
  dht.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo native USB port only
  }
  
  WiFi.mode(WIFI_STA); 
  ThingSpeak.begin(client); 

}


void loop() {

  // Connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println();
  
  // set the fields with the values
  ThingSpeak.setField(1, h);
  ThingSpeak.setField(2, t);
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  delay(15000);
}
