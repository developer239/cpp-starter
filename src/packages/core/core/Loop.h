#pragma once

#include <SDL.h>

#include <memory>
#include <vector>

#include "./IStrategy.h"
#include "./Renderer.h"
#include "./Window.h"

namespace Core {

class Loop {
  Window window;
  Renderer renderer;

  std::vector<IStrategy*> strategies;

  bool shouldQuit = false;

  double msPreviousFrame;
  double deltaTime = 0;

  SDL_Event event{};

 public:
  explicit Loop(std::vector<IStrategy*> strategies);

  void UpdateDeltaTime();

  void UpdateMsPreviousFrame();

  ~Loop();

  void Run();
};

}  // namespace Core
