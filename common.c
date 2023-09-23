#include "common.h"

void memcpy(void *dest, const void *src, uint64 n) {
  for (uint64 i = 0; i < n; i++) {
    ((char *)dest)[i] = ((char *)src)[i];
  }
}