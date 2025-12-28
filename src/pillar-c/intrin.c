#include "config.h"
#include "pillar-c/constants.h"
#include "pillar-c/types.h"
#include <pillar-c/intrin.h>

static inline pil_usize pillar_trailing_zeros_fallback(pil_usize value) {
  pil_usize count = PILLAR_ZERO;
  while ((value & PILLAR_ONE) == PILLAR_ZERO) {
    value >>= PILLAR_ONE;
    count++;
  }
  return count;
}

static inline pil_usize pillar_leading_zeros_fallback(pil_usize value) {
  pil_usize count = PILLAR_ZERO;
  pil_usize bits = PILLAR_BITS(pil_usize);
  pil_usize mask = (PILLAR_ONE << (bits - PILLAR_ONE));
  while ((value & mask) == PILLAR_ZERO && count < bits) {
    mask >>= PILLAR_ONE;
    count++;
  }
  return count;
}

static inline pil_usize pillar_popcount_fallback(pil_usize value) {
  pil_usize count = PILLAR_ZERO;
  while (value) {
    count += value & PILLAR_ONE;
    value >>= PILLAR_ONE;
  }
  return count;
}

pil_usize pillar_trailing_zeros(pil_usize value) {
  if (value == PILLAR_ZERO)
    return PILLAR_BITS(pil_usize);

#ifdef PILLAR_IS_GNU_LIKE
#ifdef PILLAR_IS_64BIT
  return __builtin_ctzll(value);
#elif defined(PILLAR_IS_32BIT)
  return __builtin_ctz(value);
#endif
#endif

  return pillar_trailing_zeros_fallback(value);
}

pil_usize pillar_leading_zeros(pil_usize value) {
  if (value == PILLAR_ZERO)
    return PILLAR_BITS(pil_usize);

#ifdef PILLAR_IS_GNU_LIKE
#ifdef PILLAR_IS_64BIT
  return __builtin_clzll(value);
#elif defined(PILLAR_IS_32BIT)
  return __builtin_clz(value);
#endif
#endif

  return pillar_leading_zeros_fallback(value);
}

pil_usize pillar_popcount(pil_usize value) {
#ifdef PILLAR_IS_GNU_LIKE
#ifdef PILLAR_IS_64BIT
  return __builtin_popcountll(value);
#elif defined(PILLAR_IS_32BIT)
  return __builtin_popcount(value);
#endif
#endif

  return pillar_popcount_fallback(value);
}