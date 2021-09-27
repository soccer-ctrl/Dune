#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("SandWorm Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::Render(SandWorm const sandWorm, Player const player, 
                      const std::vector<SDL_Point> &rocks,
                      SDL_Point start, SDL_Point finish) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  //Start point - white
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  block.x = start.x * block.w;
  block.y = start.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);  

  //End point - Red
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  block.x = finish.x * block.w;
  block.y = finish.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);  

  // Render player (yellow)
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = player.x * block.w;
  block.y = player.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render rocks (grey)
  SDL_SetRenderDrawColor(sdl_renderer, 0x80, 0x80, 0x80, 0xFF);
  for (auto rock : rocks){
    block.x = rock.x * block.w;
    block.y = rock.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  //Render Thumper (pink)
  if(player.thumperDeployed){
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xC0, 0xCB, 0xFF);
    block.x = player.thumperX * block.w;
    block.y = player.thumperY * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  if(! sandWorm.hidden){
    // Render sandWorm's body
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (SDL_Point const &point : sandWorm.body) {
      block.x = point.x * block.w;
      block.y = point.y * block.h;
      
      SDL_RenderFillRect(sdl_renderer, &block);
    }

    // Render sandWorm's head
    block.x = static_cast<int>(sandWorm.head_x) * block.w;
    block.y = static_cast<int>(sandWorm.head_y) * block.h;
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    SDL_RenderFillRect(sdl_renderer, &block);
  }
  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Time left: " + std::to_string(score) + ".   Thumpers left: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}