#pragma once
#include <Arduino.h>
#include <U8g2lib.h>

namespace config {
  inline constexpr const char username[24] = "Paracelsio";
  inline uint16_t crop = 0;
  inline constexpr const uint8_t* font = u8g2_font_amstrad_cpc_extended_8r; 
}

