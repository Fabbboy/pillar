#include <pillar-c/constants.h>
#include <pillar-c/intrin.h>
#include <pillar-c/types.h>

enum Pillar_Alignment pillar_alignment_map(Pillar_Usize align) {
  if (align > PILLAR_ALIGNMENT_1SHL4)
    return PILLAR_ALIGNMENT_1SHL4;

  return (enum Pillar_Alignment)align;
}

enum Pillar_Alignment pillar_alignment_for(Pillar_Usize size) {
  Pillar_Usize alignment = pillar_npow2(size);

  if (alignment > PILLAR_ALIGNMENT_1SHL4)
    return PILLAR_ALIGNMENT_1SHL4;

  return (enum Pillar_Alignment)alignment;
}

Pillar_Usize pillar_align_up(Pillar_Usize value,
                             enum Pillar_Alignment alignment) {
  Pillar_Usize mask = alignment - PILLAR_ONE;
  return PILLAR_AND((value + mask), ~mask);
}

Pillar_Usize pillar_align_down(Pillar_Usize value,
                               enum Pillar_Alignment alignment) {
  Pillar_Usize mask = alignment - PILLAR_ONE;
  return PILLAR_AND(value, ~mask);
}

bool pillar_is_aligned(Pillar_Usize value, enum Pillar_Alignment alignment) {
  Pillar_Usize mask = alignment - PILLAR_ONE;
  return PILLAR_AND(value, mask) == PILLAR_ZERO;
}
