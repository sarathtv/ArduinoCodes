#include <ModbusRTU.h>
HardwareSerial S(PA3,PA2);
 



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
  S.begin(9600, SERIAL_8N1);
  mb.begin(&S,PA8); // RE/DI connected to PA8
  mb.master();
  Serial.println("Server code");
}

uint16_t adc_val;
void loop() {
  
  if (!mb.slave()) {
    adc_val=analogRead(A0);
    Serial.println(adc_val);
    mb.writeHreg(1,10,adc_val,cb);    
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      }
    delay(10); 
  }
}
