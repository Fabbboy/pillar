#pragma once

#include "constants.h"
#include "types.h"

enum {
  PILLAR_STATUS_OK = PILLAR_ZERO,
  PILLAR_STATUS_START = PILLAR_ONE,
};

struct Pillar_Status {
  pil_u16 domain;
  pil_u16 code;
};

_Static_assert(sizeof(struct Pillar_Status) == sizeof(pil_u32),
               "Pillar_Status must be 32 bits in size");
_Static_assert(PILLAR_STATUS_OK == 0, "PILLAR_STATUS_OK must be zero");
_Static_assert(PILLAR_STATUS_START == 1, "PILLAR_STATUS_START must be one");

struct Pillar_Status pillar_status_ok();
struct Pillar_Status pillar_status_init(pil_u16 domain, pil_u16 code);