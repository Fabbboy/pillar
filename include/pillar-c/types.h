#pragma once

#include "pillar-c/constants.h"
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

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
  PILLAR_ALIGNMENT_1SHL0 = PILLAR_ONE << PILLAR_ZERO,  // 1
  PILLAR_ALIGNMENT_1SHL1 = PILLAR_ONE << PILLAR_ONE,   // 2
  PILLAR_ALIGNMENT_1SHL2 = PILLAR_ONE << PILLAR_TWO,   // 4
  PILLAR_ALIGNMENT_1SHL3 = PILLAR_ONE << PILLAR_THREE, // 8
  PILLAR_ALIGNMENT_1SHL4 = PILLAR_ONE << PILLAR_FOUR,  // 16
};

enum Pillar_Alignment pillar_alignment_map(pil_usize align);
enum Pillar_Alignment pillar_alignment_for(pil_usize size);

pil_usize pillar_align_up(pil_usize value, enum Pillar_Alignment alignment);
pil_usize pillar_align_down(pil_usize value, enum Pillar_Alignment alignment);
bool pillar_is_aligned(pil_usize value, enum Pillar_Alignment alignment);

struct Pillar_Layout {
  pil_u64 size;
  enum Pillar_Alignment alignment;
};

#define PILLAR_LAYOUT(T)                                                       \
  (struct Pillar_Layout) { sizeof(T), pillar_alignment_map(_Alignof(T)) }

#define PILLAR_LAYOUT_ARRAY(T, N)                                              \
  (struct Pillar_Layout) { sizeof(T) * (N), pillar_alignment_map(_Alignof(T)) }
