#pragma once

#include <vector>
#include "../math/Vec2.h"
#include "../math/Vec3.h"
#include "Camera.h"

class Projector {
 public:
  float fovFactor = 640;

  std::shared_ptr<Camera> camera;

  Projector() { camera = std::make_shared<Camera>(); }

  Vec2 Project3DPoint(Vec3 point) const {
    Vec2 projected_point = {
        (fovFactor * point.x) / point.z,
        (fovFactor * point.y) / point.z};
    return projected_point;
  }
};
