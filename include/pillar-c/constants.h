#pragma once

#include <limits.h>

enum {
  PILLAR_INVFD = -1,

  PILLAR_ZERO = 0,
  PILLAR_ONE,
  PILLAR_TWO,
  PILLAR_THREE,
  PILLAR_FOUR,
};

#define PILLAR_BITS(TYPE) (sizeof(TYPE) * CHAR_BIT)
