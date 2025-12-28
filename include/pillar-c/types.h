#pragma once

#include "pillar-c/constants.h"
#include <stddef.h>
#include <stdint.h>

typedef uint8_t pil_u8;
typedef uint16_t pil_u16;
typedef uint32_t pil_u32;
typedef uint64_t pil_u64;

typedef int8_t pil_i8;
typedef int16_t pil_i16;
typedef int32_t pil_i32;
typedef int64_t pil_i64;

typedef float pil_f32;
typedef double pil_f64;

typedef uintptr_t pil_uptr;
typedef intptr_t pil_iptr;
typedef size_t pil_usize;

enum Pillar_Alignment {
  PILLAR_ALIGNMENT_1SHL0 = PILLAR_ONE << PILLAR_ZERO,
  PILLAR_ALIGNMENT_1SHL1 = PILLAR_ONE << PILLAR_ONE,
  PILLAR_ALIGNMENT_1SHL2 = PILLAR_ONE << PILLAR_TWO,
  PILLAR_ALIGNMENT_1SHL3 = PILLAR_ONE << PILLAR_THREE,
  PILLAR_ALIGNMENT_1SHL4 = PILLAR_ONE << PILLAR_FOUR,
  PILLAR_ALIGNMENT_1SHL5 = PILLAR_ONE << PILLAR_FIVE,
  PILLAR_ALIGNMENT_1SHL6 = PILLAR_ONE << PILLAR_SIX,
  PILLAR_ALIGNMENT_1SHL7 = PILLAR_ONE << PILLAR_SEVEN,
  PILLAR_ALIGNMENT_1SHL8 = PILLAR_ONE << PILLAR_EIGHT,
  PILLAR_ALIGNMENT_1SHL9 = PILLAR_ONE << PILLAR_NINE,
  PILLAR_ALIGNMENT_1SHL10 = PILLAR_ONE << PILLAR_TEN,
};

struct Pillar_Layout {
  pil_u64 size;
  enum Pillar_Alignment alignment;
};

#define PILLAR_LAYOUT(T)                                                       \
  (struct Pillar_Layout) { sizeof(T), _Alignof(T) }

#define PILLAR_LAYOUT_ARRAY(T, N)                                              \
  (struct Pillar_Layout) { sizeof(T) * (N), _Alignof(T) }
