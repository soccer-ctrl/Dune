#include "sandWorm.h"
#include <vector>
#include <cmath>
#include <iostream>

void SandWorm::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the sandWorm head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void SandWorm::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }
  if (head_x >= grid_width-1){head_x = grid_width-1;}
  else if(head_x <= 0){head_x=0;}
  if (head_y >= grid_height-1){head_y=grid_height-1;}
  else if(head_y<=0){head_y=0;}

}

void SandWorm::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);
  if (body.size() > size){
    body.erase(body.begin());
  }
}