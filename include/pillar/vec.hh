#pragma once

#include <pillar-c/vec.h>
#include <pillar/types.hh>

template <typename T> struct Pillar_Vec {
  struct Pillar_RawVec raw;
};

template <typename T>
void pillar_vec_init(struct Pillar_Vec<T> *vec,
                     struct Pillar_Allocator allocator) {
  *vec = PILLAR_RAW_VEC_INIT(allocator, pillar_layout<T>());
}

template <typename T>
void pillar_vec_init_with(struct Pillar_Vec<T> *vec,
                          struct Pillar_Allocator allocator, Pillar_Usize cap) {
  pillar_raw_vec_init_with(&vec->raw, pillar_layout<T>(), allocator, cap);
}

template <typename T> void pillar_vec_deinit(struct Pillar_Vec<T> *vec) {
  pillar_raw_vec_deinit(&vec->raw);
}

template <typename T>
struct Pillar_Status pillar_vec_append(struct Pillar_Vec<T> *vec, T *item) {
  return pillar_raw_vec_append(&vec->raw, (Pillar_U8 *)item);
}

template <typename T>
struct Pillar_Status pillar_vec_pop(struct Pillar_Vec<T> *vec, T *out) {
  return pillar_raw_vec_pop(&vec->raw, (Pillar_U8 *)out);
}

template <typename T>
struct Pillar_Status pillar_vec_prepend(struct Pillar_Vec<T> *vec, T *item) {
  return pillar_raw_vec_prepend(&vec->raw, (Pillar_U8 *)item);
}

template <typename T>
struct Pillar_Status pillar_vec_shift(struct Pillar_Vec<T> *vec, T *out) {
  return pillar_raw_vec_shift(&vec->raw, (Pillar_U8 *)out);
}

template <typename T>
struct Pillar_Status pillar_vec_at(struct Pillar_Vec<T> *vec,
                                   Pillar_Usize index, T **out) {
  Pillar_U8 *ptr = NULL;
  struct Pillar_Status status = pillar_raw_vec_at(&vec->raw, index, &ptr);
  *out = (T *)ptr;
  return status;
}
