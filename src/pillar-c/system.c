#include "config.h"
#include "pillar-c/types.h"
#include <pillar-c/system.h>

#ifdef PILLAR_IS_POSIX
#include <sys/mman.h>
#include <unistd.h>

const Pillar_U32 PILLAR_PAGE_PROT = PROT_READ | PROT_WRITE;
const Pillar_U32 PILLAR_PAGE_FLAGS = MAP_PRIVATE | MAP_ANONYMOUS;

#else
const pil_usize PILLAR_COMMON_PGSIZE = 4096;
#endif

Pillar_Usize pillar_system_pgsize(void) {
#ifdef PILLAR_IS_POSIX
  return (Pillar_Usize)sysconf(_SC_PAGESIZE);
#else
  return PILLAR_COMMON_PGSIZE;
#endif
}

struct Pillar_Status pillar_system_map(struct Pillar_Layout layout,
                                       Pillar_U8 **out) {
  const Pillar_Usize pgalign = pillar_alignment_for(pillar_system_pgsize());
  if (!pillar_is_aligned(layout.size, pgalign))
    return PILLAR_SYSTEM_STATUS(PILLAR_SYSTEM_CODE_UNALIGNED);

  if (!pillar_is_aligned(layout.alignment, pgalign))
    return PILLAR_SYSTEM_STATUS(PILLAR_SYSTEM_CODE_UNALIGNED);

  Pillar_Usize total = layout.size + layout.alignment;

#ifdef PILLAR_IS_POSIX
  Pillar_U8 *ptr =
      mmap(NULL, total, PILLAR_PAGE_PROT, PILLAR_PAGE_FLAGS, PILLAR_INVFD, 0);
  if (ptr == MAP_FAILED)
    return PILLAR_SYSTEM_STATUS(PILLAR_SYSTEM_CODE_OOM);

  Pillar_Uptr addr = (Pillar_Uptr)ptr;
  Pillar_Uptr aligned_addr = pillar_align_up(addr, layout.alignment);
  ptr = (Pillar_U8 *)aligned_addr;

  Pillar_Usize prefix = aligned_addr - addr;
  if (prefix > 0) {
    munmap((void *)addr, prefix);
  }

  Pillar_Uptr suffix_start = aligned_addr + layout.size;
  Pillar_Usize suffix_len = (addr + total) - suffix_start;
  if (suffix_len > 0) {
    munmap((void *)suffix_start, suffix_len);
  }

  *out = ptr;
  return pillar_status_ok();
#else
  return pillar_status_init(PILLAR_SYSTEM_DOMAIN, PILLAR_SYSTEM_UNSUPPORTED);
#endif
}

struct Pillar_Status pillar_system_unmap(struct Pillar_Layout layout,
                                         Pillar_U8 *ptr) {
  const Pillar_Usize pgalign = pillar_alignment_for(pillar_system_pgsize());

  if (!pillar_is_aligned(layout.size, pgalign))
    return PILLAR_SYSTEM_STATUS(PILLAR_SYSTEM_CODE_UNALIGNED);

  if (!pillar_is_aligned((Pillar_Uptr)ptr, pgalign))
    return PILLAR_SYSTEM_STATUS(PILLAR_SYSTEM_CODE_UNALIGNED);

#ifdef PILLAR_IS_POSIX
  munmap(ptr, layout.size);
  return pillar_status_ok();
#endif
  return pillar_status_init(PILLAR_SYSTEM_DOMAIN,
                            PILLAR_SYSTEM_CODE_UNSUPPORTED);
}
