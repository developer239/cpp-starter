#pragma once

#include <vector>
#include "../math/Vec2.h"
#include "../math/Vec3.h"
#include "Camera.h"

class Projector {
  public:
    float fovFactor = 640;

    std::shared_ptr<Camera> camera;

    Projector() {
      camera = std::make_shared<Camera>();
    }

    Vec2 project3DPoint(Vec3 point) {
      Vec2 projected_point = {
          (fovFactor * point.x) / point.z,
          (fovFactor * point.y) / point.z
      };
      return projected_point;
    }

    std::vector<Vec2> project3DPointMultiple(std::vector<std::vector<Vec3>>& vertices) {
      std::vector<Vec2> projectedPoints;

      for (auto& vertex: vertices) {
        for (Vec3& point: vertex) {
          projectedPoints.push_back(project3DPoint(point));
        }
      }

      return projectedPoints;
    }
};
