#pragma once

#include "pillar-c/status.h"
#include "pillar-c/types.h"

struct Pillar_Allocator;

typedef struct Pillar_Status (*Pillar_AllocFn)(
    struct Pillar_Allocator *allocator, struct Pillar_Layout layout,
    pil_u8 **out_ptr);

typedef struct Pillar_Status (*Pillar_DeallocFn)(
    struct Pillar_Allocator *allocator, pil_u8 *ptr,
    struct Pillar_Layout layout);

struct Pillar_Allocator {
  Pillar_AllocFn alloc;
  Pillar_DeallocFn dealloc;
};