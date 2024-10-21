#include <raylib.h>

#include "rust.h"

typedef union {
  Color color;
  u32 bits;
} ColorExtended;
