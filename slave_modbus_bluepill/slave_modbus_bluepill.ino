
#include <ModbusRTU.h>
HardwareSerial S(PA3,PA2);


const int analogOutPin = PC13;

#define COIL_STAT_REG 15
#define POT_VAL 10
#define SLAVE_ID 1

ModbusRTU mb;
uint16_t pot_value=0;
void setup() {
  Serial.begin(9600);
  S.begin(9600, SERIAL_8N1);
  mb.begin(&S,PA5); // RE/DI connected to PA5 bluepill
  
  mb.slave(SLAVE_ID);
  mb.addHreg(POT_VAL);
  mb.Hreg(POT_VAL, 0);
  Serial.println("Slave code");


}

void loop() {
  //server code will update the holding register with  pot val.
  //here read the Hreg value and adjust the led brightness
     pot_value=mb.Hreg(POT_VAL);
     pot_value=map(pot_value,9,1023,0,255);
     Serial.println(pot_value);
     analogWrite(analogOutPin, pot_value);
     delay(10);
     mb.task();
     
}
