#include "player.h"
#include "helper.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <random> 



void Player::Update() {

  switch (direction) {
    case Direction::kUp:
      y -= speed;
      break;

    case Direction::kDown:
      y += speed;
      break;

    case Direction::kLeft:
      x -= speed;
      break;

    case Direction::kRight:
      x += speed;
      break;
    case Direction::kStop:
      break;
  }
  //Keep the player within the window walls
  if (x >= grid_width-1){x = grid_width-1;}
  else if(x <= 0){x=0;}
  if (y >= grid_height-1){y=grid_height-1;}
  else if(y<=0){y=0;}

}

void Player::DeployThumper(std::vector<std::vector<State>> &grid){
  if(numThumpers>0){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> randPos(0,grid.size()-1); // distribution in range [1, 6]

    int rand_x = randPos(rng);
    int rand_y = randPos(rng);

    //We can only deploy a thumper on sand, not on rock(obstacle) or
    //start and finish tiles.
    if(grid[rand_x][rand_y] == State::kEmpty){
      thumperDeployed = true;
      std::cout<<"Deploying Thumper"<<std::endl;
      thumperX = rand_x;
      thumperY = rand_y;
      numThumpers --;
    }
  }
}
