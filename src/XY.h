#ifndef XY_H_INCLUDED
#define XY_H_INCLUDED

#include <SFML/System/Vector2.hpp>

struct XY{
    XY(){};
    template <typename T>
    XY(sf::Vector2<T> v2) : x(v2.x), y(v2.y){}
    XY(int x, int y) : x(x), y(y){}
    XY operator +(const XY& xy){return XY(this->x + xy.x, this->y + xy.y);}
    XY operator -(const XY& xy){return XY(this->x - xy.x, this->y - xy.y);}
    XY operator *(const XY& xy){return XY(this->x * xy.x, this->y * xy.y);}
    XY operator /(const XY& xy){return XY(this->x / xy.x, this->y / xy.y);}
    int x, y;
};

#endif // XY_H_INCLUDED
