//modbus  code - Reading 1 holding register and 1 coil register
#include <ModbusRTU.h>
#include <SoftwareSerial.h>
 
SoftwareSerial S(D3, D2);
#define TEMP_VAL_REG 10
#define COIL_STAT_REG 15
#define SLAVE_ID 1
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
bool coil_stat= false;
void loop() {
  
  if (!mb.slave()) {
    Serial.println("reading Holding Reg");
    mb.readHreg(SLAVE_ID, TEMP_VAL_REG, coils, 1, cb);
    while(mb.slave()) { // Check if transaction is active
      mb.task();
      delay(10);
    }    
    Serial.println((float)coils[0]/100);
    //write to coil reg
    mb.writeCoil(SLAVE_ID,COIL_STAT_REG,coil_stat,cb);
    Serial.println("coil stat is" );
    Serial.print( coil_stat);
    while(mb.slave()) { // Check if transaction is active
    mb.task();
    delay(10);
    }
      
  }
  delay(1000);
  coil_stat=!coil_stat;// this variable should be set based on the mqtt cb onrecieve

}
