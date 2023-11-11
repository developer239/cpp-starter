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

    painter.ClearColorBuffer();
    painter.Mesh(*cube, *shouldCull);
    painter.BackgroundGrid();
  }

  void OnRender(Core::Window& window, Core::Renderer& renderer) override {
    painter.RenderColorBuffer(renderer);
  }
};
