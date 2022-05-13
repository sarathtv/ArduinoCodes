#include <ModbusMaster.h>               //Library for using ModbusMaster


#define MAX485_DE      8
#define MAX485_RE_NEG  2

ModbusMaster node;                    //object node for class ModbusMaster



void preTransmission()            //Function for setting stste of Pins DE & RE of RS-485
{
  digitalWrite(MAX485_RE_NEG, 1);             
  digitalWrite(MAX485_DE, 1);
}

void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup()
{
  
  pinMode(MAX485_RE_NEG, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  
  digitalWrite(MAX485_RE_NEG, 0);
  digitalWrite(MAX485_DE, 0);

  Serial.begin(115200);             //Baud Rate as 115200

  node.begin(1, Serial);            //Slave ID as 1
  node.preTransmission(preTransmission);         //Callback for configuring RS-485 Transreceiver correctly
  node.postTransmission(postTransmission);
}

void loop()
{
  float value = 101.5;
  
  node.writeSingleRegister(0x40000,value);        //Writes value to 0x40000 holding register
  
  delay(1000);
 
}
