#include <Arduino.h>
#include <U8x8lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif

U8X8_SH1106_128X64_NONAME_HW_I2C u8x8(/* reset=*/ U8X8_PIN_NONE);


// End of constructor list
float t =10.2;
float h =99.2;

void setup(void)
{

 
  u8x8.begin();
  u8x8.setPowerSave(0);
  u8x8.setFont(u8x8_font_chroma48medium8_r);
  u8x8.drawString(4,0,"Embedded ");
  u8x8.drawString(3,1,"Enthusiast!");
  
}

void loop(void)
{
  u8x8.drawString(0, 11, "Temperature:");
  u8x8.drawString(0, 12, (String(t) + "°C").c_str());
  u8x8.drawString(0, 13, "Humidity:");
  u8x8.drawString(0, 14, (String(h) + "°C").c_str());

  delay(2000);
  
}
