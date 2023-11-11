#pragma once

#include <vector>
#include "../math/Faces.h"
#include "../math/Vec.h"

class Mesh {
 public:
  std::vector<Vec<3>> vertices = {};
  std::vector<Face> faces = {};
  Vec<3> rotation;
  std::vector<std::vector<Vec<3>>> data;

  void rotate() {
    rotation.x += 0.01;
    rotation.y += 0.01;
    rotation.z += 0.01;
  }
};
