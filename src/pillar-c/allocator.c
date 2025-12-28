#include "pillar-c/status.h"
#include "pillar-c/types.h"
#include <pillar-c/allocator.h>
#include <stdlib.h>

static struct Pillar_Status
pillar_heap_alloc(struct Pillar_Allocator *allocator,
                  struct Pillar_Layout layout, pil_u8 **out) {
  (void)allocator;

  pil_u8 *ptr = (pil_u8 *)aligned_alloc(layout.alignment, layout.size);
  if (!ptr)
    return pillar_status_init(PILLAR_ALLOCATOR_DOMAIN,
                              PILLAR_ALLOCATOR_CODE_OOM);

  *out = ptr;
  return pillar_status_ok();
}

static struct Pillar_Status
pillar_heap_dealloc(struct Pillar_Allocator *allocator, pil_u8 *ptr,
                    struct Pillar_Layout layout) {
  (void)allocator;
  (void)layout;

  free(ptr);
  return pillar_status_ok();
}

struct Pillar_Allocator pillar_heap_allocator(void) {
  return PILLAR_ALLOCATOR_INIT(pillar_heap_alloc, pillar_heap_dealloc);
}

struct Pillar_Status pillar_allocator_alloc(struct Pillar_Allocator *allocator,
                                            struct Pillar_Layout layout,
                                            pil_u8 **out) {
  assert(allocator && allocator->alloc);
  return allocator->alloc(allocator, layout, out);
}
struct Pillar_Status
pillar_allocator_dealloc(struct Pillar_Allocator *allocator, pil_u8 *ptr,
                         struct Pillar_Layout layout) {
  assert(allocator && allocator->dealloc);
  return allocator->dealloc(allocator, ptr, layout);
}