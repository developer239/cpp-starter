#include "LoopStrategy.h"
#include "core/Loop.h"

int main() {
  LoopStrategy strategy;

  auto loop = Core::Loop({&strategy});
  loop.Run();
}
