#pragma once
#include <Arduino.h>

namespace device {
  struct prescript {
    uint16_t timeframe;
    char instruction[];
  };
};
