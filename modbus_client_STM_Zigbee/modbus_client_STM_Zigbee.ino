
#include <ModbusRTU.h>
HardwareSerial S(PA3,PA2);
HardwareSerial Serial_Xbee(PB11, PB10);

float InttoFloat(uint16_t Data0,uint16_t Data1) {
  float x;
  unsigned long *p;
  p = (unsigned long*)&x;
  *p = (unsigned long)Data0 << 16 | Data1; //Big-endian
  return(x);
}



ModbusRTU mb;

bool cb(Modbus::ResultCode event, uint16_t transactionId, void* data) { // Callback to monitor errors
  if (event != Modbus::EX_SUCCESS) {
    Serial.print("Request result: 0x");
    Serial.print(event, HEX);
  }
  return true;
}

void setup() {
  Serial_Xbee.begin(9600); //serial port for debug and xbee txm
  S.begin(9600, SERIAL_8E1);
  mb.begin(&S,PA8); // RE/DE connected to PA8
  mb.master();
}

uint16_t val[2];
void loop() {
 //voltage V1 
  if (!mb.slave()) {
    mb.readHreg(1, 3926, val, 2, cb); // Slave id is 1 and register address is 3926 and 
    //we are reading 2 bytes from the register and saving in val
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(100);
    }
 float voltage= InttoFloat(val[1],val[0]);
  //transmit via zigbee
  Serial_Xbee.print("Voltage=");
  Serial_Xbee.println(voltage);

      }


  //current
    if (!mb.slave()) {
    mb.readHreg(1, 3912, val, 2, cb); // Slave id is 1 and register address is 3926 and 
    //we are reading 2 bytes from the register and saving in val
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(100);
    }
 float avg_current= InttoFloat(val[1],val[0]);
  //transmit via zigbee
  Serial_Xbee.print("AverageCurrent=");
  Serial_Xbee.println(avg_current);

      }

    //frequency
      if (!mb.slave()) {
    mb.readHreg(1, 3914, val, 2, cb); // Slave id is 1 and register address is 3926 and 
    //we are reading 2 bytes from the register and saving in val
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(100);
    }
     float freq= InttoFloat(val[1],val[0]);
  //transmit via zigbee
  Serial_Xbee.print("Frequency=");
  Serial_Xbee.println(freq);
}
delay(1000);
}
