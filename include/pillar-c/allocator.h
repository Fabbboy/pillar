#pragma once

#include "pillar-c/status.h"
#include "pillar-c/types.h"
#include <assert.h>

const pil_u32 PILLAR_ALLOCATOR_DOMAIN = __COUNTER__;
enum Pillar_AllocatorCode {
  PILLAR_ALLOCATOR_CODE_OOM = PILLAR_STATUS_START,
};

struct Pillar_Allocator;

typedef struct Pillar_Status (*Pillar_AllocFn)(
    struct Pillar_Allocator *allocator, struct Pillar_Layout layout,
    pil_u8 **out);

typedef struct Pillar_Status (*Pillar_DeallocFn)(
    struct Pillar_Allocator *allocator, pil_u8 *ptr,
    struct Pillar_Layout layout);

struct Pillar_Allocator {
  Pillar_AllocFn alloc;
  Pillar_DeallocFn dealloc;
};

#define PILLAR_ALLOCATOR_INIT(ALLOC_FN, DEALLOC_FN)                            \
  (struct Pillar_Allocator) { ALLOC_FN, DEALLOC_FN }

struct Pillar_Allocator pillar_heap_allocator(void);

struct Pillar_Status pillar_allocator_alloc(struct Pillar_Allocator *allocator,
                                            struct Pillar_Layout layout,
                                            pil_u8 **out);
struct Pillar_Status
pillar_allocator_dealloc(struct Pillar_Allocator *allocator, pil_u8 *ptr,
                         struct Pillar_Layout layout);
