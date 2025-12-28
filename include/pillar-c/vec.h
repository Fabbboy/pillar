#pragma once

#include "pillar-c/allocator.h"
#include "pillar-c/status.h"
#include "pillar-c/types.h"

const pil_usize PILLAR_VEC_GROWTH = 2;
const pil_usize PILLAR_VEC_MIN = 4;

enum Pillar_VecCode {
  PILLAR_VEC_CODE_OUT_OF_BOUNDS = PILLAR_STATUS_START,
  PILLAR_VEC_CODE_INVALID_ARGUMENT,
};

#define PILLAR_VEC_STATUS(err) pillar_status_init(PILLAR_VEC_DOMAIN, err)

struct Pillar_Vec {
  pil_u8 *data;
  pil_usize len;
  pil_usize cap;
  struct Pillar_Layout layout; // updated on every resize
  struct Pillar_Allocator allocator;
};

#define PILLAR_VEC_INIT(ALLOCATOR, LAYOUT)                                     \
  (struct Pillar_Vec) { NULL, PILLAR_ZERO, PILLAR_ZERO, LAYOUT, ALLOCATOR }

struct Pillar_Status pillar_vec_init_with(struct Pillar_Vec *vec,
                                          struct Pillar_Layout layout,
                                          struct Pillar_Allocator allocator,
                                          pil_usize cap);
struct Pillar_Status pillar_vec_deinit(struct Pillar_Vec *vec);

struct Pillar_Status pillar_vec_append(struct Pillar_Vec *vec, pil_u8 *item);
struct Pillar_Status pillar_vec_pop(struct Pillar_Vec *vec, pil_u8 *out);
struct Pillar_Status pillar_vec_prepend(struct Pillar_Vec *vec, pil_u8 *item);
struct Pillar_Status pillar_vec_shift(struct Pillar_Vec *vec, pil_u8 *out);
struct Pillar_Status pillar_vec_grow(struct Pillar_Vec *vec, pil_usize new_cap);
struct Pillar_Status pillar_vec_shrink(struct Pillar_Vec *vec);