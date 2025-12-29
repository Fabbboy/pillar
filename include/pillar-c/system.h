#pragma once

#include "pillar-c/status.h"
#include "pillar-c/types.h"

enum Pillar_SystemCode {
  PILLAR_SYSTEM_CODE_OOM = PILLAR_STATUS_START,
  PILLAR_SYSTEM_CODE_UNALIGNED,
  PILLAR_SYSTEM_CODE_UNSUPPORTED,
};

#define PILLAR_SYSTEM_STATUS(err) pillar_status_init(PILLAR_SYSTEM_DOMAIN, err)

Pillar_Usize pillar_system_pgsize(void);
struct Pillar_Status pillar_system_map(struct Pillar_Layout layout,
                                       Pillar_U8 **out);
struct Pillar_Status pillar_system_unmap(struct Pillar_Layout layout,
                                         Pillar_U8 *ptr);
