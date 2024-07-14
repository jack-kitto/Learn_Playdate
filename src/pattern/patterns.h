#ifndef PATTERNS_H
#define PATTERNS_H

#include "pd_api.h"

extern LCDPattern grey50;
extern LCDPattern grey12_5;
extern LCDPattern grey25;
extern LCDPattern grey37_5;
extern LCDPattern grey62_5;
extern LCDPattern grey75;
extern LCDPattern grey87_5;
extern LCDPattern black;
extern LCDPattern white;

typedef struct Patterns {
  LCDPattern *grey12_5;
  LCDPattern *grey25;
  LCDPattern *grey37_5;
  LCDPattern *grey50;
  LCDPattern *grey62_5;
  LCDPattern *grey75;
  LCDPattern *grey87_5;
  LCDPattern *white;
  LCDPattern *black;
} Patterns;

Patterns *initialisePatterns(void);

#endif // PATTERNS_H
