#pragma once

#include "pillar-c/constants.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef uint8_t Pillar_U8;
typedef uint16_t Pillar_U16;
typedef uint32_t Pillar_U32;
typedef uint64_t Pillar_U64;

typedef int8_t Pillar_I8;
typedef int16_t Pillar_I16;
typedef int32_t Pillar_I32;
typedef int64_t Pillar_i64;

typedef float Pillar_F32;
typedef double Pillar_F64;

typedef uintptr_t Pillar_Uptr;
typedef intptr_t Pillar_Iptr;
typedef size_t Pillar_Usize;

enum Pillar_Alignment {
  PILLAR_ALIGNMENT_1SHL0 = PILLAR_ONE << PILLAR_ZERO,  // 1
  PILLAR_ALIGNMENT_1SHL1 = PILLAR_ONE << PILLAR_ONE,   // 2
  PILLAR_ALIGNMENT_1SHL2 = PILLAR_ONE << PILLAR_TWO,   // 4
  PILLAR_ALIGNMENT_1SHL3 = PILLAR_ONE << PILLAR_THREE, // 8
  PILLAR_ALIGNMENT_1SHL4 = PILLAR_ONE << PILLAR_FOUR,  // 16
};

enum Pillar_Alignment pillar_alignment_map(Pillar_Usize align);
enum Pillar_Alignment pillar_alignment_for(Pillar_Usize size);

Pillar_Usize pillar_align_up(Pillar_Usize value,
                             enum Pillar_Alignment alignment);
Pillar_Usize pillar_align_down(Pillar_Usize value,
                               enum Pillar_Alignment alignment);
bool pillar_is_aligned(Pillar_Usize value, enum Pillar_Alignment alignment);

struct Pillar_Layout {
  Pillar_U64 size;
  enum Pillar_Alignment alignment;
};

#define PILLAR_LAYOUT(T)                                                       \
  (struct Pillar_Layout) { sizeof(T), pillar_alignment_map(_Alignof(T)) }

#define PILLAR_LAYOUT_ARRAY(T, N)                                              \
  (struct Pillar_Layout) { sizeof(T) * (N), pillar_alignment_map(_Alignof(T)) }

#define PILLAR_LAYOUT_COPY(LAYOUT, SIZE)                                       \
  (struct Pillar_Layout) { SIZE, (LAYOUT).alignment }
