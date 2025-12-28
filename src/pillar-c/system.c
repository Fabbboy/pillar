#include "config.h"
#include "pillar-c/types.h"
#include <pillar-c/system.h>

#ifdef PILLAR_IS_POSIX
#include <sys/mman.h>
#include <unistd.h>

const pil_u32 PILLAR_PAGE_PROT = PROT_READ | PROT_WRITE;
const pil_u32 PILLAR_PAGE_FLAGS = MAP_PRIVATE | MAP_ANONYMOUS;

#else
const pil_usize PILLAR_COMMON_PGSIZE = 4096;
#endif

pil_usize pillar_system_pgsize(void) {
#ifdef PILLAR_IS_POSIX
  return (pil_usize)sysconf(_SC_PAGESIZE);
#else
  return PILLAR_COMMON_PGSIZE;
#endif
}

struct Pillar_Status pillar_system_map(struct Pillar_Layout layout,
                                       pil_u8 **out) {
  const pil_usize pgalignment = pillar_alignment_for(pillar_system_pgsize());
  if (!pillar_is_aligned(layout.size, pgalignment))
    return PILLAR_SYSTEM_STATUS(PILLAR_SYSTEM_STATUS_UNALIGNED);

  if (!pillar_is_aligned(layout.size, pgalignment))
    return PILLAR_SYSTEM_STATUS(PILLAR_SYSTEM_STATUS_UNALIGNED);

  pil_usize total = pillar_align_up(layout.size, pgalignment);

#ifdef PILLAR_IS_POSIX
  pil_u8 *ptr =
      mmap(NULL, total, PILLAR_PAGE_PROT, PILLAR_PAGE_FLAGS, PILLAR_INVFD, 0);
  if (ptr == MAP_FAILED)
    return PILLAR_SYSTEM_STATUS(PILLAR_SYSTEM_STATUS_OOM);

  *out = ptr;
  return pillar_status_ok();
#else
  return pillar_status_init(PILLAR_SYSTEM_DOMAIN, PILLAR_SYSTEM_UNSUPPORTED);
#endif
}

struct Pillar_Status pillar_system_unmap(struct Pillar_Layout layout,
                                         pil_u8 *ptr) {
#ifdef PILLAR_IS_POSIX
  munmap(ptr, layout.size);
  return pillar_status_ok();
#endif
  return pillar_status_init(PILLAR_SYSTEM_DOMAIN, PILLAR_SYSTEM_UNSUPPORTED);
}
