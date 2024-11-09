#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "food.h"
#include <future>
#include <algorithm>
#include <mutex>

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void Render(Snake const snake, Food &food);
  void Render(Snake const snake, Food &food, std::promise<bool>&& prms);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  void ClearScreen();
  std::shared_ptr<SDL_Rect> RenderFood(std::shared_ptr<SDL_Rect> block, const Snake& snake, Food& food);
  std::shared_ptr<SDL_Rect> RenderSnake(std::shared_ptr<SDL_Rect> block, const Snake& snake);
  void RenderFood(const Snake& snake, Food& food);
  void RenderSnake(const Snake& snake);
  void drawBody(std::shared_ptr<SDL_Rect> block, SDL_Point p);
  std::mutex renderMutex;
};

#endif