#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SSD1306_128X64_NONAME_F_HW_I2C display(
  U8G2_R0,
  U8X8_PIN_NONE
);

void setup() {
  display.begin();
}

void loop() {
  display.clearBuffer();

  display.setFont(u8g2_font_amstrad_cpc_extended_8r);
  display.drawStr(0, 50, "Hello OLED!");

  display.sendBuffer();

  delay(1000);
}
