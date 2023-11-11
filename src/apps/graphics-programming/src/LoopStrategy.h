#pragma once

#include "core/AssetStore.h"
#include "core/IStrategy.h"
#include "core/Window.h"
#include "logger/Logger.h"
#include "rendering/Painter.h"
#include "rendering/WavefrontLoader.h"
#include "geometry/Cube.h"

class LoopStrategy : public Core::IStrategy {
 public:
  // TODO: why the hell are these uniq pointers?
  std::shared_ptr<Cube> cube;
  std::shared_ptr<bool> shouldRotate;
  std::shared_ptr<bool> shouldCull;

  // TODO: pass width and height from window instance
  Painter painter = Painter(800, 600);

  void Init(Core::Window& window, Core::Renderer& renderer) override {
    cube = std::make_shared<Cube>();

    shouldRotate = std::make_shared<bool>(false);
    shouldCull = std::make_shared<bool>(false);

    WavefrontLoader::LoadObjFile("assets/models/f22.obj", *cube);
  }

  void HandleEvent(SDL_Event& event) override {}

  void OnUpdate(
      Core::Window& window, Core::Renderer& renderer, double deltaTime
  ) override {
    if (*shouldRotate) {
      cube->rotate();
    }
  }

  void OnRender(Core::Window& window, Core::Renderer& renderer) override {
    painter.ClearColorBuffer(0xFFFFFFFF);
    painter.BackgroundGrid();

    std::vector<Triangle> trianglesToRender;

    // Loop all triangle faces of our mesh
    for (int i = 0; i < cube->faces.size(); i++) {
      auto meshFace = cube->faces[i];

      std::vector<Vec3> faceVertices(3);

      faceVertices[0] = cube->vertices[meshFace.a - 1];
      faceVertices[1] = cube->vertices[meshFace.b - 1];
      faceVertices[2] = cube->vertices[meshFace.c - 1];

      std::vector<Vec3> transformedVertices(3);

      // Loop all three vertices of this current face and apply transformations
      for (int j = 0; j < 3; j++) {
        Vec3 transformed_vertex = faceVertices[j];

        transformed_vertex = transformed_vertex.rotateX(cube->rotation.x);
        transformed_vertex = transformed_vertex.rotateY(cube->rotation.y);
        transformed_vertex = transformed_vertex.rotateZ(cube->rotation.z);

        // Translate the vertices away from the camera
        transformed_vertex.z += 5;

        // Save transformed vertex in the array of transformed vertices
        transformedVertices[j] = transformed_vertex;
      }

      if (*shouldCull) {
        // Check backface culling
        Vec3 vector_a = transformedVertices[0]; /*   A   */
        Vec3 vector_b = transformedVertices[1]; /*  / \  */
        Vec3 vector_c = transformedVertices[2]; /* C---B */

        // Get the vector subtraction of B-A and C-A
        Vec3 vector_ab = vector_b - vector_a;
        Vec3 vector_ac = vector_c - vector_a;

        // Compute the face normal (using cross product to find perpendicular)
        Vec3 normal = vector_ab.CrossProduct(vector_ac);

        // Find the vector between a point in the triangle and the camera origin
        Vec3 camera_ray = painter.projector->camera->position - vector_a;

        float dot_normal_camera = normal.Normalize().DotProduct(camera_ray.Normalize());

        // Bypass the triangles that are looking away from the camera
        if (dot_normal_camera < 0) {
          continue;
        }
      }

      Triangle projected_triangle;

      // Loop all three vertices to perform projection
      for (int j = 0; j < 3; j++) {
        // Project the current vertex
        Vec2 projected_point = painter.projector->project3DPoint(transformedVertices[j]);

        // Scale and translate the projected points to the middle of the screen
        projected_point.x += (window.GetWidth() / 2);
        projected_point.y += (window.GetHeight() / 2);

        if (j == 0) {
          projected_triangle.p1 = projected_point;
        } else if (j == 1) {
          projected_triangle.p2 = projected_point;
        } else if (j == 2) {
          projected_triangle.p3 = projected_point;
        }
      }

      // Save the projected triangle in the array of triangles to render
      trianglesToRender.push_back(projected_triangle);
    }

    int num_triangles = trianglesToRender.size();
    for (int i = 0; i < num_triangles; i++) {
      Triangle triangle = trianglesToRender[i];

      // Draw unfilled triangle
      painter.DrawFilledTriangle(
          triangle.p1.x, triangle.p1.y, // vertex A
          triangle.p2.x, triangle.p2.y, // vertex B
          triangle.p3.x, triangle.p3.y, // vertex C
          0xFF00FF00
      );
      painter.Triangle(
          triangle.p1.x, triangle.p1.y, // vertex A
          triangle.p2.x, triangle.p2.y, // vertex B
          triangle.p3.x, triangle.p3.y, // vertex C
          0xFF000000
      );
    }

    painter.Render(renderer);
  }
};
