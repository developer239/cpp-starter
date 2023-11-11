#pragma once

#include "imgui.h"

#include "../geometry/Cube.h"
#include "../rendering/Projector.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

// TODO: rename to controls
class Debug {
 public:
  void Render(bool& shouldRotate, bool& shouldCull) {
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

    ImGui::Render();
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
  };
};
