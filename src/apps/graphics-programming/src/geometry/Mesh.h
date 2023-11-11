#pragma once

#include <vector>
#include "../math/Faces.h"
#include "../math/Vec3.h"

class Mesh {
 public:
  std::vector<Vec3> vertices = {};
  std::vector<Face> faces = {};
  Vec3 rotation = {0, 0, 0};
  std::vector<std::vector<Vec3>> data;

  void rotate() {
    rotation.x += 0.01;
    rotation.y += 0.01;
    rotation.z += 0.01;
  }
};
