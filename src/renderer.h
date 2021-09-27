#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "sandWorm.h"
#include "player.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(SandWorm const sandWorm, Player const player, 
  const std::vector<SDL_Point> &rocks,
  SDL_Point start, SDL_Point finish);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif