#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "SDL.h"
#include "helper.h"

class Player {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight , kStop};
  Player(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height) {}
  void Update();
  void DeployThumper(std::vector<std::vector<State>> &grid);

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  float x;
  float y;
  float thumperX;
  float thumperY;
  int numThumpers{1};
  bool thumperDeployed = false;
  bool alive = true;
  bool won = false;

 private:
  int grid_width;
  int grid_height;
};

#endif