#include "game.h"
#include "math.h" 
#include <iostream>
#include <vector>
#include "SDL.h"
#include "helper.h"
using namespace std;

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : sandWorm(grid_width-1, grid_height-1),
      player(grid_width-1, grid_height-1),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)) {

  //Create a 2d grid, initially defining every grid location as empty.
  grid.resize(grid_height, vector<State>(grid_width, State::kEmpty));

  //Player start position is upper left-hand corner
  start = {0,0};
  grid[start.x][start.y] = State::kStart;

  //Goal (finish position) is the lower right-hand corner
  finish = {int(grid_width-1), int(grid_height-1)};
  grid[finish.x][finish.y] = State::kFinish;

  PlacePlayer();
  PlaceRocks(); //This will update the grid to define rock positions
  
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
               
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

    
  //Game Loop (Input, Update, Render) 
  while (running) {

    frame_start = SDL_GetTicks();

    //Handle user input
    controller.HandleInput(running, player, grid);
    
    //if the player is on rock, set the worm to be hidden
    sandWorm.hidden = false;
    for(auto rock : rocks){
      if (Collision(player.x, player.y, rock.x, rock.y)) sandWorm.hidden = true;
    }
    //The worm is also hidden when the player is on the start position
    if (Collision(player.x, player.y, start.x, start.y)) sandWorm.hidden = true;
    
    //Handle sandworm behaviour
    controller.HandleInput(running, sandWorm, player, grid);

    Update();

    renderer.Render(sandWorm, player, rocks, start, finish);
    
    frame_end = SDL_GetTicks();
    // Keep track of how long each loop through the input/update/render cycle takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      timeRemaining --;
      renderer.UpdateWindowTitle(timeRemaining, player.numThumpers);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }

    //Check if any thumpers have been eaten
    if(player.thumperDeployed){
      if(Collision(player.thumperX, player.thumperY, sandWorm.head_x, sandWorm.head_y)){
        player.thumperDeployed = false;
      }
    }

    //Check if game has ended

    //If the worm has eaten the player
    if(Collision(static_cast<int>(player.x), static_cast<int>(player.y), static_cast<int>(sandWorm.head_x), static_cast<int>(sandWorm.head_y))){
      player.alive = false;
      std::cout<<"Worm has eaten player!"<<endl;
      break;
    }
    //If the player has finished the game
    if(Collision(static_cast<int>(player.x), static_cast<int>(player.y), static_cast<int>(finish.x), static_cast<int>(finish.y))){
      player.won = true;
      std::cout<<"Player has won!"<<std::endl;
      break;
    }
    //If the player has run out of time
    if(timeRemaining <=0 ){
      player.alive = false;
      std::cout<<"Time is up. You have succumbed to the harsh desert climate of Arrakis!"<<std::endl;
      break;
    }
  }
}

void Game::PlacePlayer() {
  player.x = start.x;
  player.y = start.y;
}

void Game::PlaceRocks() {
  int numRocks = 8; //This is the number of rocks (safe points)
  for (int i=0;i<numRocks;i++){
    SDL_Point rock;
    int x,y;
    while(true){
      x = random_w(engine);
      y = random_h(engine);
      // Check that the location is not occupied by a sandWorm item or a player item 
      // or start / finish before placing rock.
      if(grid[x][y] == State::kEmpty){
        grid[x][y] = (State::kRock); //define the x,y position as an rock in 2D grid
        rock.x = x;
        rock.y = y;
        rocks.emplace_back(rock);
        break;
      }
    }
  }
}

void Game::Update() {
  player.Update();
  sandWorm.Update();
}

int Game::GetTimeRemaining() const { return timeRemaining; }