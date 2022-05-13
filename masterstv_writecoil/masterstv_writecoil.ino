#include <ModbusRTU.h>
#include <SoftwareSerial.h>
 
SoftwareSerial S(D3, D2);


ModbusRTU mb;

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Callback to monitor errors
  if (event != Modbus::EX_SUCCESS) {
    Serial.print("Request result: 0x");
    Serial.print(event, HEX);
  }
  return true;
}

void setup() {
  Serial.begin(9600);
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S,D0); // RE/DI connected to D0 of ESP8266
  mb.master();
}

bool relayval=true;
bool coilval[2];
void loop() {
  //read to coil
  // write to coil
  //toggle value

  if (!mb.slave()) {
   Serial.println("reading coil reg");
    mb.readCoil(1, 15, coilval, 1, cb);
    while(mb.slave()) 
    { 
      mb.task();
      delay(10);
    }
   Serial.println(coilval[0]);
  //read complete

  //begin write coil
  mb.writeCoil(1,15,relayval,cb);
  while(mb.slave()) { // Check if transaction is active
  mb.task();
  delay(10);
    }
  //write complete 
  }
  relayval=!relayval;
  delay(1000);
}
/*
if (!mb.slave()) {
    Serial.println("reading coil reg");
    mb.readCoil(1, 15, coilval, 1, cb);
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(10);
    }
    Serial.println(coilval[0]);

   //write coil reg
   mb.writeCoil(1,15,0,cb);
   while(mb.slave()) { // Check if transaction is active
   mb.task();
   delay(10);
      
  }
  delay(1000);
  }*/
