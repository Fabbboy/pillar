#include "pillar-c/status.h"
#include "pillar-c/types.h"
#include <pillar-c/vec.h>
#include <string.h>

static inline pil_usize pillar_vec_offset_at(const struct Pillar_Vec *vec,
                                             pil_usize index) {
  return index * vec->layout.size;
}

static inline pil_usize pillar_vec_cap_bytes(const struct Pillar_Vec *vec) {
  return vec->cap * vec->layout.size;
}

static inline pil_usize pillar_vec_len_bytes(const struct Pillar_Vec *vec) {
  return vec->len * vec->layout.size;
}

static inline pil_usize pillar_vec_new_cap(pil_usize desired_cap) {
  return desired_cap > PILLAR_VEC_MIN ? desired_cap : PILLAR_VEC_MIN;
}

struct Pillar_Status pillar_vec_init_with(struct Pillar_Vec *vec,
                                          struct Pillar_Layout layout,
                                          struct Pillar_Allocator allocator,
                                          pil_usize cap) {
  if (!vec || !pillar_allocator_validate(&allocator))
    return PILLAR_VEC_STATUS(PILLAR_VEC_CODE_INVALID_ARGUMENT);

  pil_usize cap_bytes = layout.size * cap;
  struct Pillar_Layout total_layout = PILLAR_LAYOUT_COPY(layout, cap_bytes);
  struct Pillar_Status status =
      pillar_allocator_alloc(&allocator, total_layout, &vec->data);

  if (!pillar_status_is_ok(status))
    return status;

  vec->len = PILLAR_ZERO;
  vec->cap = cap;
  vec->layout = layout;
  vec->allocator = allocator;
  return pillar_status_ok();
}

struct Pillar_Status pillar_vec_deinit(struct Pillar_Vec *vec) {
  if (!vec)
    return PILLAR_VEC_STATUS(PILLAR_VEC_CODE_INVALID_ARGUMENT);

  return pillar_allocator_dealloc(&vec->allocator, vec->data, vec->layout);
}

struct Pillar_Status pillar_vec_grow(struct Pillar_Vec *vec,
                                     pil_usize new_cap) {
  if (!vec)
    return PILLAR_VEC_STATUS(PILLAR_VEC_CODE_INVALID_ARGUMENT);

  if (new_cap <= vec->cap)
    return pillar_status_ok();

  pil_usize new_cap_bytes = vec->layout.size * new_cap;
  struct Pillar_Layout new_layout =
      PILLAR_LAYOUT_COPY(vec->layout, new_cap_bytes);
  pil_u8 *new_data;

  struct Pillar_Status status =
      pillar_allocator_alloc(&vec->allocator, new_layout, &new_data);
  if (!pillar_status_is_ok(status))
    return status;

  pil_usize len_bytes = pillar_vec_len_bytes(vec);
  memcpy(new_data, vec->data, len_bytes);

  pil_usize old_cap_bytes = pillar_vec_cap_bytes(vec);
  struct Pillar_Layout old_layout =
      PILLAR_LAYOUT_COPY(vec->layout, old_cap_bytes);
  pillar_allocator_dealloc(&vec->allocator, vec->data, old_layout);

  vec->data = new_data;
  vec->cap = new_cap;
  vec->layout = new_layout;

  return pillar_status_ok();
}

struct Pillar_Status pillar_vec_shrink(struct Pillar_Vec *vec) {
  if (!vec)
    return PILLAR_VEC_STATUS(PILLAR_VEC_CODE_INVALID_ARGUMENT);

  if (vec->len == vec->cap)
    return pillar_status_ok();

  if (vec->len == PILLAR_ZERO) {
    pil_usize cap_bytes = pillar_vec_cap_bytes(vec);
    struct Pillar_Layout old_layout =
        PILLAR_LAYOUT_COPY(vec->layout, cap_bytes);
    pillar_allocator_dealloc(&vec->allocator, vec->data, old_layout);
    vec->data = NULL;
    vec->cap = PILLAR_ZERO;
    vec->layout = PILLAR_LAYOUT_COPY(vec->layout, PILLAR_ZERO);
    return pillar_status_ok();
  }

  pil_usize len_bytes = pillar_vec_len_bytes(vec);
  struct Pillar_Layout new_layout = PILLAR_LAYOUT_COPY(vec->layout, len_bytes);
  pil_u8 *new_data;

  struct Pillar_Status status =
      pillar_allocator_alloc(&vec->allocator, new_layout, &new_data);
  if (!pillar_status_is_ok(status))
    return status;

  memcpy(new_data, vec->data, len_bytes);

  pil_usize cap_bytes = pillar_vec_cap_bytes(vec);
  struct Pillar_Layout old_layout = PILLAR_LAYOUT_COPY(vec->layout, cap_bytes);
  pillar_allocator_dealloc(&vec->allocator, vec->data, old_layout);

  vec->data = new_data;
  vec->cap = vec->len;
  vec->layout = new_layout;

  return pillar_status_ok();
}

struct Pillar_Status pillar_vec_append(struct Pillar_Vec *vec, pil_u8 *item) {
  if (!vec || !item)
    return PILLAR_VEC_STATUS(PILLAR_VEC_CODE_INVALID_ARGUMENT);

  if (vec->len == vec->cap) {
    pil_usize new_cap = pillar_vec_new_cap(vec->cap * PILLAR_VEC_GROWTH);
    struct Pillar_Status status = pillar_vec_grow(vec, new_cap);
    if (!pillar_status_is_ok(status))
      return status;
  }

  pil_usize offset = pillar_vec_offset_at(vec, vec->len);
  memcpy(vec->data + offset, item, vec->layout.size);
  vec->len++;

  return pillar_status_ok();
}

struct Pillar_Status pillar_vec_pop(struct Pillar_Vec *vec, pil_u8 *out) {
  if (!vec || !out)
    return PILLAR_VEC_STATUS(PILLAR_VEC_CODE_INVALID_ARGUMENT);

  if (vec->len == PILLAR_ZERO)
    return PILLAR_VEC_STATUS(PILLAR_VEC_CODE_OUT_OF_BOUNDS);

  vec->len--;
  pil_usize offset = pillar_vec_offset_at(vec, vec->len);
  memcpy(out, vec->data + offset, vec->layout.size);

  return pillar_status_ok();
}

struct Pillar_Status pillar_vec_prepend(struct Pillar_Vec *vec, pil_u8 *item) {
  if (!vec || !item)
    return PILLAR_VEC_STATUS(PILLAR_VEC_CODE_INVALID_ARGUMENT);

  if (vec->len == vec->cap) {
    pil_usize new_cap = pillar_vec_new_cap(vec->cap * PILLAR_VEC_GROWTH);
    struct Pillar_Status status = pillar_vec_grow(vec, new_cap);
    if (!pillar_status_is_ok(status))
      return status;
  }

  pil_usize shift_bytes = pillar_vec_len_bytes(vec);
  memmove(vec->data + vec->layout.size, vec->data, shift_bytes);
  memcpy(vec->data, item, vec->layout.size);
  vec->len++;

  return pillar_status_ok();
}

struct Pillar_Status pillar_vec_shift(struct Pillar_Vec *vec, pil_u8 *out) {
  if (!vec || !out)
    return PILLAR_VEC_STATUS(PILLAR_VEC_CODE_INVALID_ARGUMENT);

  if (vec->len == PILLAR_ZERO)
    return PILLAR_VEC_STATUS(PILLAR_VEC_CODE_OUT_OF_BOUNDS);

  memcpy(out, vec->data, vec->layout.size);
  vec->len--;

  pil_usize shift_bytes = pillar_vec_len_bytes(vec);
  memmove(vec->data, vec->data + vec->layout.size, shift_bytes);

  return pillar_status_ok();
}