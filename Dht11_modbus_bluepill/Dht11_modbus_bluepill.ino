/*Server
bluepill communicates DHT11 data with nodemcu via modbus.
nodemcu transfers data to adafruit via mqtt
From adafruit you get actuation messages , Nodemcu recieves it and sends to bluepill via modbus
Relay 
DHT 11
bluepill
add Hreg and coil reg
update hreg values 
read coil reg values
*/
/************** Header Files **********************/
#include <ModbusRTU.h>
#include "DHT.h"
/***************Macro Definitions******************/
#define DHTPIN PB12
#define DHTTYPE DHT11   // DHT 11
#define COIL_STAT_REG 15
#define TEMP_VAL_REG 10
#define SLAVE_ID 1
/**************Function declarations***************/
void read_Temperature();
/**************Object Creations********************/
HardwareSerial S(PA3,PA2);
DHT dht(DHTPIN, DHTTYPE);
ModbusRTU mb;
/**************Global Variables********************/
float t;
bool prev_status=false;
/************************************/
void setup() {
  Serial.begin(9600);
  dht.begin();
  S.begin(9600, SERIAL_8N1);
  mb.begin(&S,PA5); // RE/DI connected to PA5 bluepill
  
  mb.slave(SLAVE_ID);
// Add Holding register and write 0 value
  mb.addHreg(TEMP_VAL_REG);
  mb.Hreg(TEMP_VAL_REG, 0);
// Add coil register and write 0  value
  mb.addCoil(COIL_STAT_REG);
  mb.Coil(COIL_STAT_REG,0);
  Serial.println("Server code");
}

void loop() 
{
  read_Temperature();//read temperature value
  mb.Hreg(TEMP_VAL_REG,t*100);
  readCoilReg();
  delay(1000);
  mb.task();
     
}

void read_Temperature()
{
  t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println();
}

void readCoilReg()
{
  bool current_stat=mb.Coil(COIL_STAT_REG);
  Serial.println("Coil stat is :");
  Serial.print(current_stat);
  if(current_stat!=prev_status)
  {
    prev_status=current_stat;
    //write to relay  
  }
}
