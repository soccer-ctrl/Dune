#include "player.h"
#include "helper.h"
#include <cmath>
#include <iostream>
#include <vector> 



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
    //We can only deploy a thumper on sand, not on rock(obstacle) or
    //start and finish tiles.
    if(grid[x][y] ==State::kEmpty){
      thumperDeployed = true;
      std::cout<<"Deploying Thumper"<<std::endl;
      thumperX = x;
      thumperY = y;
      numThumpers --;
    }
  }
}