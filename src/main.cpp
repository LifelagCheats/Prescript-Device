#include "HardwareSerial.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <cfg.hpp>
#include <prng.hpp>
#include <prescripts.hpp>

U8G2_SSD1306_128X64_NONAME_1_HW_I2C display(
  U8G2_R0,
  U8X8_PIN_NONE
);


inline void append(char* buf, size_t bufSize, size_t& pos, const char* s) {
    if (!s) return;
    size_t n = strlen(s);
    if (pos + n >= bufSize) n = bufSize - pos - 1;
    memcpy(buf + pos, s, n);
    pos += n;
    buf[pos] = '\0';
}

inline void append_P(char* buf, size_t bufSize, size_t& pos, const char* s) {
    if (!s) return;
    size_t n = strlen_P(s);
    if (pos + n >= bufSize) n = bufSize - pos - 1;
    memcpy_P(buf + pos, s, n);
    pos += n;
    buf[pos] = '\0';
}


static void buildHowToFind(char* out, size_t outSize, Mulberry32& rng,
                           const char* adj, const char* super,
                           const char* ptype, const char* color,
                           const char* clothing, int n1, int n5, int n8) {
    char ptypeBuf[40];
    strncpy_P(ptypeBuf, ptype, sizeof(ptypeBuf) - 1);
    ptypeBuf[sizeof(ptypeBuf) - 1] = '\0';   

    char adjBuf[24];
    strncpy_P(adjBuf, adj, sizeof(adjBuf) - 1);
    adjBuf[sizeof(adjBuf) - 1] = '\0';

    char superBuf[24];
    strncpy_P(superBuf, super, sizeof(superBuf) - 1);
    superBuf[sizeof(superBuf) - 1] = '\0';

    char colorBuf[16];
    strncpy_P(colorBuf, color, sizeof(colorBuf) - 1);
    colorBuf[sizeof(colorBuf) - 1] = '\0';

    uint32_t which = rng.rand_int(10);
    switch (which) {
        case 0: snprintf_P(out, outSize, PSTR("a %s"), ptypeBuf); break;
        case 1: snprintf_P(out, outSize, PSTR("the %s %s"), adjBuf, ptypeBuf); break;
        case 2: snprintf_P(out, outSize, PSTR("the %s %s"), superBuf, ptypeBuf); break;
        case 3: snprintf_P(out, outSize, PSTR("someone in %s%s"), colorBuf, clothing); break;
        case 4: snprintf_P(out, outSize, PSTR("the %d%s %s"), n1,
                         (n1 % 10 == 1 && n1 != 11) ? "st" :
                         (n1 % 10 == 2 && n1 != 12) ? "nd" :
                         (n1 % 10 == 3 && n1 != 13) ? "rd" : "th", ptypeBuf); break;
        case 5: snprintf_P(out, outSize, PSTR("the closest %s"), ptypeBuf); break;
        case 6: snprintf_P(out, outSize, PSTR("the %s person nearby"), adjBuf); break;
        case 7: snprintf_P(out, outSize, PSTR("the last person to talk to you")); break;
        case 8: snprintf_P(out, outSize, PSTR("someone you recognize but don't know")); break;
        case 9: snprintf_P(out, outSize, PSTR("whoever you choose")); break;
    }
};

static void buildTask1(char* out, size_t outSize, Mulberry32& rng,
                       const char* target, const char* topic, const char* game,
                       const char* obj, const char* extra) {
    char topicBuf[32];
    strncpy_P(topicBuf, topic, sizeof(topicBuf) - 1);
    topicBuf[sizeof(topicBuf) - 1] = '\0';

    char gameBuf[32];
    strncpy_P(gameBuf, game, sizeof(gameBuf) - 1);
    gameBuf[sizeof(gameBuf) - 1] = '\0';    

    char extraBuf[32];
    strncpy_P(extraBuf, extra, sizeof(extraBuf) - 1);
    extraBuf[sizeof(extraBuf) - 1] = '\0';

    char objBuf[32];
    strncpy_P(objBuf, obj, sizeof(objBuf) - 1);
    objBuf[sizeof(objBuf) - 1] = '\0';   

    uint32_t which = rng.rand_int(20);
    switch (which) {
        case 0:  snprintf_P(out, outSize, PSTR("observe %s from a distance"), target); break;
        case 1:  snprintf_P(out, outSize, PSTR("stand near %s without speaking"), target); break;
        case 2:  snprintf_P(out, outSize, PSTR("follow %s briefly, then stop"), target); break;
        case 3:  snprintf_P(out, outSize, PSTR("ask %s about %s"), target, topicBuf); break;
        case 4:  snprintf_P(out, outSize, PSTR("play %s with %s"), gameBuf, target); break;
        case 5:  snprintf_P(out, outSize, PSTR("go to a concert with %s"), target); break;
        case 6:  snprintf_P(out, outSize, PSTR("kiss %s%s"), target, extraBuf); break;
        case 7:  snprintf_P(out, outSize, PSTR("punch %s and beat them down%s"), target, extraBuf); break;
        case 8:  snprintf_P(out, outSize, PSTR("give a love letter to %s"), target); break;
        case 9:  snprintf_P(out, outSize, PSTR("share an observation about %s with %s"), topicBuf, target); break;
        case 10: snprintf_P(out, outSize, PSTR("interact with %s"), target); break;
        case 11: snprintf_P(out, outSize, PSTR("yell at %s about %s"), target, topicBuf); break;
        case 12: snprintf_P(out, outSize, PSTR("have a debate about %s"), topicBuf); break;
        case 13: snprintf_P(out, outSize, PSTR("sleep alongside %s"), target); break;
        case 14: snprintf_P(out, outSize, PSTR("play with %s"), target); break;
        case 15: snprintf_P(out, outSize, PSTR("make the %s bleed"), target); break;
        case 16: snprintf_P(out, outSize, PSTR("lie to %s"), target); break;
        case 17: snprintf_P(out, outSize, PSTR("have a race with %s"), target); break;
        case 18: snprintf_P(out, outSize, PSTR("hit %s with the first %s you find"), target, objBuf); break;
        case 19: snprintf_P(out, outSize, PSTR("give this prescript to %s"), target); break;
    }
};

static void buildTask3(char* out, size_t outSize, Mulberry32& rng,
                       const char* location, const char* obj, const char* extra,
                       int n2, int n7, int n8) {
    char locBuf[32];
    strncpy_P(locBuf, location, sizeof(locBuf) - 1);
    locBuf[sizeof(locBuf) - 1] = '\0';

    char objBuf[32];
    strncpy_P(objBuf, obj, sizeof(objBuf) - 1);
    objBuf[sizeof(objBuf) - 1] = '\0';

    char extraBuf[32];
    strncpy_P(extraBuf, extra, sizeof(extraBuf) - 1);
    extraBuf[sizeof(extraBuf) - 1] = '\0';

    uint32_t which = rng.rand_int(15);
    switch (which) {
        case 0:  snprintf_P(out, outSize, PSTR("draw a picture of a %s"), locBuf); break;
        case 1:  snprintf_P(out, outSize, PSTR("locate a %s"), locBuf); break;
        case 2:  snprintf_P(out, outSize, PSTR("dig a grave at a %s"), locBuf); break;
        case 3:  snprintf_P(out, outSize, PSTR("order a pizza and pay with exactly %d coins"), n8); break;
        case 4:  snprintf_P(out, outSize, PSTR("drink %d cups of water%s"), n8, extraBuf); break;
        case 5:  snprintf_P(out, outSize, PSTR("eat only fish%s"), extraBuf); break;
        case 6:  snprintf_P(out, outSize, PSTR("start a fire")); break;
        case 7:  snprintf_P(out, outSize, PSTR("kick a %s"), objBuf); break;
        case 8:  snprintf_P(out, outSize, PSTR("light a candle and watch it burn for %d minutes"), n8); break;
        case 9:  snprintf_P(out, outSize, PSTR("sit and do nothing for %d minutes"), n8); break;
        case 10: snprintf_P(out, outSize, PSTR("count backwards from %d"), n8); break;
        case 11: snprintf_P(out, outSize, PSTR("walk until your feet hurt, then walk %d more steps"), n7); break;
        case 12: snprintf_P(out, outSize, PSTR("go to a %s"), locBuf); break;
        case 13: snprintf_P(out, outSize, PSTR("stand still for %d hours%s"), n8, extraBuf); break;
        case 14: snprintf_P(out, outSize, PSTR("do a backflip%s"), extraBuf); break;
    }
}

static char gPrescriptBuf[300];

const char* generatePrescript(Mulberry32& rng) {
    char* out = gPrescriptBuf;
    size_t bufSize = sizeof(gPrescriptBuf);
    size_t pos = 0;
    out[0] = '\0';

    const char* location = LOCATIONS[rng.rand_int(N(LOCATIONS))];
    int israndom         = rng.rand_int(150);                         
    if (israndom == 4) {
        return PREPRESCRIPT[rng.rand_int(N(PREPRESCRIPT))];
    };

    const char* personAdj    = PERSON_ADJ[rng.rand_int(N(PERSON_ADJ))];
    const char* personSuper  = PERSON_SUPER[rng.rand_int(N(PERSON_SUPER))];
    const char* color1       = COLORS[rng.rand_int(N(COLORS))];
    const char* ptype        = PERSONTYPE[rng.rand_int(N(PERSONTYPE))];

    int isperson = rng.rand_int(2);

    int n1  = rng.rand_int(150) + 1;
    int n7  = rng.rand_int(100) + 1;
    int n2  = rng.rand_int(400) + 1;
    int n5  = rng.rand_int(6) + 1;
    int n8  = rng.rand_int(7) + 1;

    char clothing1[32];
    snprintf_P(clothing1, sizeof(clothing1), PSTR("%S%S"),
             MATERIAL[rng.rand_int(N(MATERIAL))],
             CLOTHING[rng.rand_int(N(CLOTHING))]);

    const char* game = GAMES[rng.rand_int(N(GAMES))];

    char howtofind[64];
    buildHowToFind(howtofind, sizeof(howtofind), rng,
                   personAdj, personSuper, ptype, color1, clothing1,
                   n1, n5, n8);

    const char* obj = OBJCS[rng.rand_int(N(OBJCS))];
    const char* topic = TOPICS[rng.rand_int(N(TOPICS))];

    const char* task0  = TASK0[rng.rand_int(N(TASK0))];
    const char* starter = STARTER[rng.rand_int(N(STARTER))];
    const char* extra  = ADDITIONAL[rng.rand_int(N(ADDITIONAL))];

    append_P(out, bufSize, pos, task0);
    append_P(out, bufSize, pos, starter);

    if (isperson == 1) {
        char task1[128];
        buildTask1(task1, sizeof(task1), rng, howtofind, topic, game, obj, extra);
        append(out, bufSize, pos, task1);

        int followA = rng.rand_int(3);
        if (followA == 2) {
            const char* transition = TRANSITIONS[rng.rand_int(N(TRANSITIONS))];
            const char* followup   = FOLLOWUPS[rng.rand_int(N(FOLLOWUPS))];
            append_P(out, bufSize, pos, transition);
            append_P(out, bufSize, pos, followup);
        } else {
            append(out, bufSize, pos, ".");
        }

        int followB = rng.rand_int(4);
        if (followB == 2) {
            append(out, bufSize, pos, " ");
            append_P(out, bufSize, pos, FOLLOWUPS2[rng.rand_int(N(FOLLOWUPS2))]);
        }
    } else {
        char task3[128];
        buildTask3(task3, sizeof(task3), rng, location, obj, extra, n2, n7, n8);
        append(out, bufSize, pos, task3);

        int followB = rng.rand_int(4);
        if (followB == 2) {
            append(out, bufSize, pos, " ");
            append_P(out, bufSize, pos, FOLLOWUPS2[rng.rand_int(N(FOLLOWUPS2))]);
        }
    }

    if (out[0] >= 'a' && out[0] <= 'z') out[0] -= 32;

    return out;
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  config::crop = random(1, 32768);
  prng rng;
  xmur3 hasher(rng.seed());
  uint32_t xmurhash = hasher();
  Mulberry32 sappling(xmurhash);
  display.begin();
  Serial.println(rng.seed());
  Serial.println(xmurhash);
  const char* prescript = generatePrescript(sappling);
  Serial.println(prescript);
}

void loop() {
  display.clearBuffer();

  display.setFont(config::font);
  display.drawStr(0, 50, "Hello OLED!");

  display.sendBuffer();

  delay(1000);
}
