#ifndef CORPORIGIDO_H
#define CORPORIGIDO_H
#include "vector2.h"

class CorpoRigido{
public:
    Vector2 posicao;
    Vector2 velocidade;
    double raio;
    double massa;

    CorpoRigido(Vector2 pos = Vector2(), Vector2 velo = Vector2(),double r = 1.0f, double m = 1.0f)
        : posicao(pos), velocidade(velo),raio(r), massa(m) {}

    void aplicarForca(const Vector2& forca, double deltaTempo)
    {
        Vector2 aceleracao = forca * (1/massa); //f = m * a, estamos mudando o vetor de forca
        velocidade += aceleracao * deltaTempo;
    }

    void atualizar(double deltaTempo)
    {
        posicao += velocidade * deltaTempo;
    }
};

#endif