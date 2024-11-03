#pragma once

#include <raylib.h>
#include <stdint.h>

typedef union {
  Color color;
  uint32_t bits;
} ColorExtended;
