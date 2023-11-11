#include "./Loop.h"

namespace Core {

Loop::Loop(std::vector<IStrategy*> strategies)
    : renderer(window.Get()), strategies(std::move(strategies)), msPreviousFrame(SDL_GetTicks()) {
  for (auto strategy : this->strategies) {
    strategy->Init(window, renderer);
  }
}

void Loop::Run() {
  while (!shouldQuit) {
    UpdateDeltaTime();
    UpdateMsPreviousFrame();

    while (SDL_PollEvent(&event)) {
      for (auto& strategy : strategies) {
        strategy->HandleEvent(event);
      }

      if (event.type == SDL_QUIT) {
        shouldQuit = true;
      }
    }

    for (auto& strategy : strategies) {
      strategy->OnBeforeRender(window, renderer);
    }

    for (auto& strategy : strategies) {
      strategy->OnUpdate(window, renderer, deltaTime);
      strategy->OnRender(window, renderer);
    }

    for (auto& strategy : strategies) {
      strategy->OnAfterRender(window, renderer);
    }

    renderer.Render();
  }
}

void Loop::UpdateDeltaTime() {
  deltaTime = (SDL_GetTicks() - msPreviousFrame) / 1000.0;
}

void Loop::UpdateMsPreviousFrame() {
  msPreviousFrame = SDL_GetTicks();
}


Loop::~Loop() { SDL_Quit(); }

}  // namespace Core
