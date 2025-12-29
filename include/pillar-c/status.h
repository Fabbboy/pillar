#pragma once

#include "constants.h"
#include "types.h"

const Pillar_U16 PILLAR_SYSTEM_DOMAIN = __LINE__;
const Pillar_U16 PILLAR_ALLOCATOR_DOMAIN = __LINE__;
const Pillar_U16 PILLAR_VEC_DOMAIN = __LINE__;

enum {
  PILLAR_STATUS_OK = PILLAR_ZERO,
  PILLAR_STATUS_START = PILLAR_ONE,
};

struct Pillar_Status {
  Pillar_U16 domain;
  Pillar_U16 code;
};

_Static_assert(sizeof(struct Pillar_Status) == sizeof(Pillar_U32),
               "Pillar_Status must be 32 bits in size");
_Static_assert(PILLAR_STATUS_OK == 0, "PILLAR_STATUS_OK must be zero");
_Static_assert(PILLAR_STATUS_START == 1, "PILLAR_STATUS_START must be one");

struct Pillar_Status pillar_status_ok();
struct Pillar_Status pillar_status_init(Pillar_U16 domain, Pillar_U16 code);
static inline bool pillar_status_is_ok(struct Pillar_Status status) {
  return status.code == PILLAR_STATUS_OK;
}