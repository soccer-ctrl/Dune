#ifndef SANDWORM_H
#define SANDWORM_H

#include <vector>
#include "SDL.h"

class SandWorm {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  SandWorm(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 2),
        head_y(grid_height / 2) {}

  void Update();

  bool SnakeCell(int x, int y);

  Direction direction = Direction::kUp;

  float speed{0.12f};
  int size{4};
  bool alive{true};
  float head_x;
  float head_y;
  bool hidden{false};
  int grid_width;
  int grid_height;
  std::vector<SDL_Point> body;

 private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

};

#endif