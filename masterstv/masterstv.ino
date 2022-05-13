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

uint16_t coils[2];
bool coilval[2];
void loop() {
  
  if (!mb.slave()) {
    Serial.println("reading coil reg");
    mb.readCoil(1, 15, coilval, 1, cb);
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(10);
    }
    Serial.println(coilval[0]);

    Serial.println("reading Holding Reg");
    mb.readHreg(1, 10, coils, 1, cb);
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(10);
    }    
    Serial.println(coils[0]);
      
  }
  delay(1000);
  
//  if (!mb.slave()) {
//    Serial.println("reading Holding Reg");
//    mb.readHreg(1, 10, coils, 1, cb);
//    while(mb.slave()) { // Check if transaction is active
//      mb.task();
//      delay(10);
//    }    
//    Serial.println(coils[0]);
//  }
}




/*
void loop() {
  
  if (!mb.slave()) {

    Serial.println("reading coil reg");
    mb.readCoil(1, 15, coilval, 1, cb);
    Serial.println(coilval[0]);
    Serial.println("reading Holding Reg");
    mb.readHreg(1, 10, coils, 1, cb);
    Serial.println(coils[0]);
    
    
  }
  
  mb.task();
  yield();
  delay(1000);
}
*/
