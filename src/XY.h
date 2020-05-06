#ifndef XY_H_INCLUDED
#define XY_H_INCLUDED

#include <SFML/System/Vector2.hpp>

struct XY{
    XY(){};
    XY(sf::Vector2i v2i) : x(v2i.x), y(v2i.y){};
    XY(int x, int y) : x(x), y(y){}
    int x, y;
};

#endif // XY_H_INCLUDED
