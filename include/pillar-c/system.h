#pragma once

#include "pillar-c/status.h"
#include "pillar-c/types.h"

enum Pillar_SystemStatus {
  PILLAR_SYSTEM_STATUS_OOM = PILLAR_STATUS_START,
  PILLAR_SYSTEM_STATUS_UNALIGNED,
  PILLAR_SYSTEM_UNSUPPORTED,
};

#define PILLAR_SYSTEM_STATUS(err) pillar_status_init(PILLAR_SYSTEM_DOMAIN, err)

pil_usize pillar_system_pgsize(void);
struct Pillar_Status pillar_system_map(struct Pillar_Layout layout,
                                       pil_u8 **out);
struct Pillar_Status pillar_system_unmap(struct Pillar_Layout layout,
                                         pil_u8 *ptr);
