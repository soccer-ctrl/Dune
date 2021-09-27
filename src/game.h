#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "sandWorm.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetTimeRemaining() const;

 private:
  SandWorm sandWorm;
  Player player;
  SDL_Point start;
  SDL_Point finish;
  std::vector<SDL_Point> rocks;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  //This is the amount of time in seconds that the player has to reach the goal.
  int timeRemaining{30};
  std::vector<std::vector<State>> grid;

  void PlacePlayer();
  void PlaceRocks();
  void Update();
};

#endif