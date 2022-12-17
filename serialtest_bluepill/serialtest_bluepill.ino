HardwareSerial Serial2(PB11, PB10);
HardwareSerial S(PA10, PA9);
void setup() {
  // put your setup code here, to run once:

 Serial2.begin(9600);
 S.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial2.println("hello");
S.println("helloss");
delay(500);
}
