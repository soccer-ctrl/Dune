#include "helper.h"
#include <iostream>

bool Collision(float r1x, float r1y, float r2x, float r2y) {

  // are the sides of one rectangle touching the other?
  if (r1x + 0.5 >= r2x - 0.5 &&    // r1 right edge past r2 left
      r1x - 0.5 <= r2x + 0.5 &&    // r1 left edge past r2 right
      r1y - 0.5 <= r2y + 0.5 &&    // r1 top edge past r2 bottom
      r1y + 0.5 >= r2y - 0.5) {    // r1 bottom edge past r2 top
    return true;
  }
  return false;
}