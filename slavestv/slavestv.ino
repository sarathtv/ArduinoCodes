// modbus SLAVE code for accessing two regsister -1 holding register and 1 coil register
#include <ModbusRTU.h>
#include <SoftwareSerial.h>
 
SoftwareSerial S(D3, D2);

#define REGN 10
#define REG_COIL 15
#define SLAVE_ID 1

ModbusRTU mb;

void setup() {
  S.begin(9600, SWSERIAL_8N1);
  mb.begin(&S,D0); // RE/DI connected to D0 of ESP8266
  
  mb.slave(SLAVE_ID);
  mb.addHreg(REGN);
  mb.Hreg(REGN, 13);
  
  mb.addCoil(REG_COIL);
  mb.Coil(REG_COIL,1);

}

void loop() {
  mb.task();
  yield();
}
