#include <ModbusRTU.h>
#include <SoftwareSerial.h>

float InttoFloat(uint16_t Data0,uint16_t Data1) {
  float x;
  unsigned long *p;
  p = (unsigned long*)&x;
  *p = (unsigned long)Data0 << 16 | Data1; //Big-endian
  return(x);
}
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
uint16_t coilval[2];
void loop() {
  
  if (!mb.slave()) {
    Serial.println("reading reg1");
     mb.readHreg(1, 3926, coilval, 2, cb);
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(10);
    }
    Serial.println(coilval[0]);
    Serial.println(coilval[1]);
  float voltage= InttoFloat(coilval[1],coilval[0]);
  Serial.println("voltage= ");
  Serial.println(voltage);

      }
  delay(1000);
}
