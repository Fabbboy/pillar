#pragma once

#include "pillar-c/types.h"

template <typename T> struct Pillar_Layout pillar_layout() {
  return (struct Pillar_Layout){sizeof(T), pillar_alignment_map(_Alignof(T))};
}