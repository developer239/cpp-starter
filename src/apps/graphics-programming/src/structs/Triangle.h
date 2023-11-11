#pragma once

#include <vector>
#include "Vec2.h"

struct Triangle {
 public:
  Vec2 p1;
  Vec2 p2;
  Vec2 p3;

  explicit Triangle(
      Vec2 p1 = Vec2(0, 0), Vec2 p2 = Vec2(0, 0), Vec2 p3 = Vec2(0, 0)
  )
      : p1(p1), p2(p2), p3(p3) {}
};
