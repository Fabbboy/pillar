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

struct Pillar_RawVec {
  pil_u8 *data;
  pil_usize len;
  pil_usize cap;
  struct Pillar_Layout layout; // updated on every resize
  struct Pillar_Allocator allocator;
};

#define PILLAR_RAW_VEC_INIT(ALLOCATOR, LAYOUT)                                 \
  (struct Pillar_RawVec) { NULL, PILLAR_ZERO, PILLAR_ZERO, LAYOUT, ALLOCATOR }

struct Pillar_Status pillar_raw_vec_init_with(struct Pillar_RawVec *vec,
                                              struct Pillar_Layout layout,
                                              struct Pillar_Allocator allocator,
                                              pil_usize cap);
struct Pillar_Status pillar_raw_vec_deinit(struct Pillar_RawVec *vec);

struct Pillar_Status pillar_raw_vec_append(struct Pillar_RawVec *vec,
                                           pil_u8 *item);
struct Pillar_Status pillar_raw_vec_pop(struct Pillar_RawVec *vec, pil_u8 *out);
struct Pillar_Status pillar_raw_vec_prepend(struct Pillar_RawVec *vec,
                                            pil_u8 *item);
struct Pillar_Status pillar_raw_vec_shift(struct Pillar_RawVec *vec,
                                          pil_u8 *out);
struct Pillar_Status pillar_raw_vec_grow(struct Pillar_RawVec *vec,
                                         pil_usize new_cap);
struct Pillar_Status pillar_raw_vec_shrink(struct Pillar_RawVec *vec);
struct Pillar_Status pillar_raw_vec_at(struct Pillar_RawVec *vec,
                                       pil_usize index, pil_u8 **out);