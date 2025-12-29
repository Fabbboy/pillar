#include "pillar-c/status.h"

struct Pillar_Status pillar_status_ok() {
  return (struct Pillar_Status){PILLAR_STATUS_OK, PILLAR_STATUS_OK};
}

struct Pillar_Status pillar_status_init(Pillar_U16 domain, Pillar_U16 code) {
  return (struct Pillar_Status){domain, code};
}