#pragma once

#include <limits.h>

#ifdef __cplusplus
  #define _Static_assert static_assert
  #define _Alignof alignof
#endif

enum {
  PILLAR_INVFD = -1,

  PILLAR_ZERO = 0,
  PILLAR_ONE,
  PILLAR_TWO,
  PILLAR_THREE,
  PILLAR_FOUR,
};

#define PILLAR_BITS(TYPE) (sizeof(TYPE) * CHAR_BIT)
#define PILLAR_AND(value, mask) ((value) & (mask))