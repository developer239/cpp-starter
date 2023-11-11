#pragma once

#include <vector>
#include "../structs/Vec3.h"

class Camera {
  public:
    Vec3 position;

    Camera() {
      position = Vec3(0, 0, -5);
    }
};

