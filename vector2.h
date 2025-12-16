#include <cmath>
#ifndef VECTOR2_h
#define VECTOR2_h

class Vector2{
public:
    double x, y;

    Vector2(double x = 0.0f, double y = 0.0f) : x(x), y(y) {}

    //operator é uma keyword para definir uma operacao
    Vector2 operator+ (const Vector2& v) const //const para nao alterar os valores dos vetores a somar, apenas criar um novo vetor c = a + b
    {
        return Vector2(x + v.x, y + v.y);
    }
    
    Vector2 operator- (const Vector2& v) const //const para nao alterar os valores dos vetores a somar, apenas criar um novo vetor c = a + b
    {
        return Vector2(x - v.x, y - v.y);
    }

    Vector2 operator* (double escalar) const
    {
        return Vector2(x * escalar, y * escalar);
    }

    Vector2& operator+=(const Vector2& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    double comprimento() const
    {
        return sqrt(x*x + y*y);
    }

};

#endif