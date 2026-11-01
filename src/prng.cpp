#include <prng.hpp>
#include <Arduino.h>
#include <cfg.hpp>
#include <string.h>

prng::prng() {
    char num[6];
    char hex[6];

    strcpy(seed_, config::username);
    itoa(config::crop, num, 10);
    sprintf_P(hex, PSTR("%04X"), config::crop);
    strcat(seed_, num);
    strcat(seed_, hex);
}

const char* prng::seed() const {
  return seed_;
}
