#include "controller.h"
#include <iostream>
#include <vector>
#include <random>
#include "SDL.h"
#include "player.h"
#include "sandWorm.h"
#include "controller.h"
#include "helper.h"

void Controller::ChangeDirection(Player &player, Player::Direction input,
                                 Player::Direction opposite) const {
  if (player.direction != opposite) player.direction = input;
  else if (player.direction == opposite) player.direction = Player::Direction::kStop;
  return;
}

void Controller::ChangeDirection(SandWorm &sandWorm, SandWorm::Direction input) const {
                                   
  sandWorm.direction = input;
  return;
}


void Controller::HandleInput(bool &running, Player &player, std::vector<std::vector<State>> &grid) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(player, Player::Direction::kUp,
                          Player::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(player, Player::Direction::kDown,
                          Player::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(player, Player::Direction::kLeft,
                          Player::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(player, Player::Direction::kRight,
                          Player::Direction::kLeft);
          break;
        
        case SDLK_SPACE:
          player.DeployThumper(grid);
      }
    }
  }
}

void Controller::HandleInput(bool &running, SandWorm &sandWorm, Player &player, std::vector<std::vector<State>> &grid) const {
  //Get closest neighbouring grid to player direction 

  float bestDistance = 9999.0;
  int bestI = 0;
  std::vector<int> randomIvalues;
  //If no thumper has been deployed, the target is the player. Otherwise the target will be the thumper.
  float targetX;
  float targetY;

  if(player.thumperDeployed){
    targetX = player.thumperX;
    targetY = player.thumperY;
  }
  else{
    targetX = player.x;
    targetY = player.y;
  }

  for (int i = 0; i < 4; i++) {
    //Using directional deltas for N, S, E, W
    int x2 = sandWorm.head_x + delta[i][0];
    int y2 = sandWorm.head_y + delta[i][1];

    if (x2 < sandWorm.grid_width-1 && x2 >-1 && grid[x2][y2] == State::kEmpty){
      //if the sandWorm is hidden, add this non-obstacle direction to a vector 
      // for random selection of the direction.
      if(sandWorm.hidden){
          randomIvalues.emplace_back(i);
      }
      //if the sandWorm is not hidden, get the best direction
      else{
        //Get Euclidean distance
        //float distance = sqrt(pow(x2 - targetX, 2) + pow(y2 - targetY, 2) * 1.0);

        // Get Manhattan distance
        float distance =  abs(x2 - targetX) + abs(y2 - targetY);

        if (distance < bestDistance){
          bestDistance = distance;
          bestI = i; //This will give the direction with the shortest distance to target
        }
      }   
    }
  }

  if(sandWorm.hidden){
    //set the bestI to a random selection
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> selection(0,randomIvalues.size());
    bestI = randomIvalues[selection(rng)];
  }

  switch (bestI){
    case 0:
    ChangeDirection(sandWorm, SandWorm::Direction::kLeft);
    break;

    case 1:
    ChangeDirection(sandWorm, SandWorm::Direction::kUp);
    break;

    case 2:
    ChangeDirection(sandWorm, SandWorm::Direction::kRight);
    break;

    case 3:
    ChangeDirection(sandWorm, SandWorm::Direction::kDown);
    break;
  } 
}