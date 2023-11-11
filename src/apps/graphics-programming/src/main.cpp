#include "LoopStrategy.h"
#include "core-imgui/Strategy.h"
#include "core/Loop.h"

int main() {
  // TODO: uncomment strategy
  // TODO: step by step move stuff from loopstrategy init to gui strategy
  // TODO: step by step move stuff from Debug to gui strategy
//  CoreImGui::Strategy gui;
  LoopStrategy strategy;

  auto loop = Core::Loop({&strategy});
  loop.Run();
}
