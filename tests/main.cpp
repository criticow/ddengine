#include <ddengine/util/logger.hpp>
#include "game.hpp"

int main()
{
  Game game(1280, 720, 1280, 720, "Game");
  game.run();
}