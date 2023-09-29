#include "common.h"

void delay() {
  for (int i = 0; i < 0xFFFFFFF; i++)
    ;
}

void *memset(void *s, int c, uint64 n) {
  unsigned char *p = s;
  while (n--) {
    *p++ = (unsigned char)c;
  }

  return s;
}

void *memcpy(void *dest, const void *src, uint64 n) {
  unsigned char *d = dest;
  const unsigned char *s = src;
  while (n--)
    *d++ = *s++;
  return dest;
}