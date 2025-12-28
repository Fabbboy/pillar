#include <pillar-c/constants.h>
#include <pillar-c/intrin.h>
#include <pillar-c/types.h>

enum Pillar_Alignment pillar_alignment_map(pil_usize align) {
  if (align > PILLAR_ALIGNMENT_1SHL4)
    return PILLAR_ALIGNMENT_1SHL4;

  return (enum Pillar_Alignment)align;
}

enum Pillar_Alignment pillar_alignment_for(pil_usize size) {
  if (size <= PILLAR_ONE)
    return PILLAR_ALIGNMENT_1SHL0;

  pil_usize x = size - PILLAR_ONE;
  pil_usize shift =
      PILLAR_BITS(pil_usize) - PILLAR_ONE - pillar_leading_zeros(x);

  pil_usize alignment = PILLAR_ONE << shift;

  if (alignment > PILLAR_ALIGNMENT_1SHL4)
    return PILLAR_ALIGNMENT_1SHL4;

  return (enum Pillar_Alignment)alignment;
}

pil_usize pillar_align_up(pil_usize value, enum Pillar_Alignment alignment) {
  pil_usize mask = alignment - PILLAR_ONE;
  return (value + mask) & ~mask;
}

pil_usize pillar_align_down(pil_usize value, enum Pillar_Alignment alignment) {
  pil_usize mask = alignment - PILLAR_ONE;
  return value & ~mask;
}

bool pillar_is_aligned(pil_usize value, enum Pillar_Alignment alignment) {
  pil_usize mask = alignment - PILLAR_ONE;
  return (value & mask) == PILLAR_ZERO;
}
