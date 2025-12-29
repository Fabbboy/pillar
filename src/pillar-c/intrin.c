#include "config.h"
#include "pillar-c/constants.h"
#include "pillar-c/types.h"
#include <pillar-c/intrin.h>

static inline Pillar_Usize pillar_trailing_zeros_fallback(Pillar_Usize value) {
  Pillar_Usize count = PILLAR_ZERO;
  while (PILLAR_AND(value, PILLAR_ONE) == PILLAR_ZERO) {
    value >>= PILLAR_ONE;
    count++;
  }
  return count;
}

static inline Pillar_Usize pillar_leading_zeros_fallback(Pillar_Usize value) {
  Pillar_Usize count = PILLAR_ZERO;
  Pillar_Usize bits = PILLAR_BITS(Pillar_Usize);
  Pillar_Usize mask = (PILLAR_ONE << (bits - PILLAR_ONE));
  while (PILLAR_AND(value, mask) == PILLAR_ZERO && count < bits) {
    mask >>= PILLAR_ONE;
    count++;
  }
  return count;
}

static inline Pillar_Usize pillar_popcount_fallback(Pillar_Usize value) {
  Pillar_Usize count = PILLAR_ZERO;
  while (value) {
    count += PILLAR_AND(value, PILLAR_ONE);
    value >>= PILLAR_ONE;
  }
  return count;
}

Pillar_Usize pillar_trailing_zeros(Pillar_Usize value) {
  if (value == PILLAR_ZERO)
    return PILLAR_BITS(Pillar_Usize);

#ifdef PILLAR_IS_GNU_LIKE
#ifdef PILLAR_IS_64BIT
  return __builtin_ctzll(value);
#elif defined(PILLAR_IS_32BIT)
  return __builtin_ctz(value);
#endif
#endif

  return pillar_trailing_zeros_fallback(value);
}

Pillar_Usize pillar_leading_zeros(Pillar_Usize value) {
  if (value == PILLAR_ZERO)
    return PILLAR_BITS(Pillar_Usize);

#ifdef PILLAR_IS_GNU_LIKE
#ifdef PILLAR_IS_64BIT
  return __builtin_clzll(value);
#elif defined(PILLAR_IS_32BIT)
  return __builtin_clz(value);
#endif
#endif

  return pillar_leading_zeros_fallback(value);
}

Pillar_Usize pillar_popcount(Pillar_Usize value) {
#ifdef PILLAR_IS_GNU_LIKE
#ifdef PILLAR_IS_64BIT
  return __builtin_popcountll(value);
#elif defined(PILLAR_IS_32BIT)
  return __builtin_popcount(value);
#endif
#endif

  return pillar_popcount_fallback(value);
}

Pillar_Usize pillar_npow2(Pillar_Usize value) {
  if (value <= PILLAR_ONE)
    return PILLAR_ONE;

  Pillar_Usize leading_zeros = pillar_leading_zeros(value - PILLAR_ONE);
  Pillar_Usize bits = PILLAR_BITS(Pillar_Usize);
  Pillar_Usize shift = bits - leading_zeros;

  return PILLAR_ONE << shift;
}

Pillar_Usize pillar_ppow2(Pillar_Usize value) {
  if (value == PILLAR_ZERO)
    return PILLAR_ONE;

  Pillar_Usize leading_zeros = pillar_leading_zeros(value);
  Pillar_Usize bits = PILLAR_BITS(Pillar_Usize);
  Pillar_Usize shift = bits - leading_zeros - PILLAR_ONE;

  return PILLAR_ONE << shift;
}