#include "food.h"

SDL_Point& Food::getPosition()
{
    return _position;
}

void Food::setPosition(const SDL_Point& point)
{
    _position.x = point.x;
    _position.y = point.y;
}

int Food::getLifespan()
{
    return _lifespan;
}

void Food::setColor(Color& color)
{
    _color._r = color._r;
    _color._g = color._g;
    _color._b = color._b;
    _color._a = color._a;
}

Color& Food::getColor()
{
    switch (_ftype)
    {
    case FoodType::kNormal:
        _color._r = 0xbf;
        _color._g = 0x11;
        _color._b = 0x43;
        break;
    case FoodType::kDoublePoints: //efdc2e
        _color._r = 0xef;
        _color._g = 0xdc;
        _color._b = 0x3e;
        break;
    case FoodType::kLowSpeed: //2ed6ef
        _color._r = 0x2e;
        _color._g = 0xd6;
        _color._b = 0xef;
        break;
    default:
        std::cout<<"getColor\n";
        _color._r = 0xbf;
        _color._g = 0xdb;
        _color._b = 0x43;
        break;
    }
    return _color;
}

void Food::selectType()
{
    int _rand = random_type(engine);
    if(_rand<6){
        _ftype =FoodType::kNormal;
    }
    else if (_rand>6 && _rand<8)
    {
        _ftype =FoodType::kDoublePoints;
    }
    else if (_rand>8 && _rand<10)
    {
        _ftype =FoodType::kLowSpeed;
    }
    
}

Food::FoodType Food::getType()
{
    return _ftype;
}