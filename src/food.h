#ifndef FOOD_H
#define FOOD_H
#include <memory>
#include "SDL.h"
#include <iostream>
#include <random>
//#include "scores.h"
struct Color{ //bfdb43
    size_t _r{0xbf};
    size_t _g{0x11};
    size_t _b{0x43};
    float _a{1};
};

class Food{
  

  public:
    enum class FoodType{kNormal, kLowSpeed, kDoublePoints};
    Food():engine(dev()),
        random_type(0, static_cast<int>(10 - 1)){
        //std::cout<<"Food Instance created\n";
        //_position = std::make_unique<SDL_Point>();
        //_color = std::make_unique<Color>();
        
    }
    SDL_Point& getPosition();
    void setPosition(const SDL_Point& point);
    int getLifespan();
    void setColor(Color& color);
    Color&  getColor();
    void selectType();
    FoodType getType();
    
    
  private:
    int _lifespan{10};
    Color _color;
    SDL_Point _position;
    FoodType _ftype = FoodType::kNormal;
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_type;
    
};
#endif