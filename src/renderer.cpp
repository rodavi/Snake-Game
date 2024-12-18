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
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
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

void Renderer::Render(Snake const snake, SDL_Point const &food) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body) {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

//void Renderer::Render(Snake const snake, Food &food) {
Snake Renderer::Render(Snake&& snake, Food &food) {
  /*SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;*/
  std::shared_ptr<SDL_Rect> block = std::make_shared<SDL_Rect>();
  block->w = screen_width / grid_width;
  block->h = screen_height / grid_height;
  // Clear screen
  ClearScreen();
  // Render food
  block = RenderFood(block, snake, food);
  /*auto food_color = food.getColor();
  SDL_SetRenderDrawColor(sdl_renderer, food_color._r, food_color._g, food_color._b, food_color._a);
  auto food_position = food.getPosition();
  block.x = food_position.x * block.w;
  block.y = food_position.y * block.h;
  SDL_RenderFillRect(sdl_renderer, &block);

  SDL_SetRenderDrawColor(sdl_renderer, food_color._r, food_color._g, food_color._b, food_color._a);
  block.x = food_position.x * block.w;
  block.y = food_position.y* block.h;
  SDL_RenderFillRect(sdl_renderer, &block);*/
  // Render Snake
  block = RenderSnake(block, snake);
  // Update Screen
  SDL_RenderPresent(sdl_renderer);

  return std::move(snake);
}

void Renderer::Render(Snake const snake, Food &food, std::promise<bool>&& prms)
{
  std::shared_ptr<SDL_Rect> block = std::make_shared<SDL_Rect>();
  block->w = screen_width / grid_width;
  block->h = screen_height / grid_height;
  // Clear screen
  ClearScreen();
  // Render food
  block = RenderFood(block, snake, food);
  // Render Snake
  block = RenderSnake(block, snake);
  // Update Screen
  SDL_RenderPresent(sdl_renderer);

  prms.set_value(true);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::ClearScreen()
{
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);
}

std::shared_ptr<SDL_Rect> Renderer::RenderFood(std::shared_ptr<SDL_Rect> block, const Snake& snake, Food& food)
{
  auto food_color = food.getColor();
  SDL_SetRenderDrawColor(sdl_renderer, food_color._r, food_color._g, food_color._b, food_color._a);
  auto food_position = food.getPosition();
  block->x = food_position.x * block->w;
  block->y = food_position.y * block->h;
  SDL_RenderFillRect(sdl_renderer, block.get());

  SDL_SetRenderDrawColor(sdl_renderer, food_color._r, food_color._g, food_color._b, food_color._a);
  block->x = food_position.x * block->w;
  block->y = food_position.y* block->h;
  SDL_RenderFillRect(sdl_renderer, block.get());

  return block;
}

std::shared_ptr<SDL_Rect> Renderer::RenderSnake(std::shared_ptr<SDL_Rect> block, const Snake& snake)
{
  // Render snake's body in parallel
  SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

  size_t numThreads = std::thread::hardware_concurrency();  // Get number of threads supported by the hardware
  size_t chunkSize = snake.body.size() / numThreads;
  std::vector<std::thread> threads;
  //for (SDL_Point const &point : snake.body) {
  for (size_t i = 0; i < numThreads; ++i){
    /*block->x = point.x * block->w;
    block->y = point.y * block->h;
    SDL_RenderFillRect(sdl_renderer, block.get());*/

    size_t start = i * chunkSize;
    size_t end = (i == numThreads - 1) ? snake.body.size() : (i + 1) * chunkSize;

    threads.push_back(std::thread([=]() {
        for (size_t j = start; j < end; ++j) {
            drawBody(block, snake.body[j]);
        }
    }));
  }

  // Join all threads
  for (auto& t : threads) {
      t.join();
  }

  // Render snake's head
  block->x = static_cast<int>(snake.head_x) * block->w;
  block->y = static_cast<int>(snake.head_y) * block->h;
  if (snake.alive) {
    SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
  } else {
    SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer, block.get());

  return block;
}

void Renderer::drawBody(std::shared_ptr<SDL_Rect> block, SDL_Point p)
{
    block->x = p.x * block->w;
    block->y = p.y * block->h;

    std::lock_guard<std::mutex> lock(renderMutex); // SDL_RenderFillRect is not thread-safe thus mutex is needed.
    SDL_RenderFillRect(sdl_renderer, block.get());
}