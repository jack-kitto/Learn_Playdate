#pragma once
#ifndef PATTERNS_H
#define PATTERNS_H
#include <stdint.h>
typedef uint8_t LCDPattern[16]; // 8x8 pattern: 8 rows image data, 8 rows mask

typedef enum Pattern {
  PATTERN_GREY12_5,
  PATTERN_GREY25,
  PATTERN_GREY37_5,
  PATTERN_GREY50,
  PATTERN_GREY62_5,
  PATTERN_GREY75,
  PATTERN_GREY87_5,
  PATTERN_WHITE,
  PATTERN_BLACK,
} Pattern;

LCDPattern *getPattern(Pattern p);

#endif // PATTERNS_H
