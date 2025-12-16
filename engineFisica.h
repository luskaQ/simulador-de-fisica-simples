#ifndef ENGINEFISICA_H
#define ENGINEFISICA_H

#include <vector>
#include "corpoRigido.h"
#include <iostream>

class EngineFisica
{
private:
    std::vector<CorpoRigido *> corpos;

public:
    std::vector<CorpoRigido *> getCorpos()
    {
        return corpos;
    }
    void adicionarCorpo(CorpoRigido *corpo)
    {
        corpos.push_back(corpo);
    }

    void atualizar(double deltaTempo)
    {
        for (auto &corpo : corpos)
        {
            corpo->atualizar(deltaTempo);
        }
    }

    bool checarColisao(const CorpoRigido &corpoA, const CorpoRigido &corpoB)
    {

        Vector2 vetorDiferenca = corpoA.posicao - corpoB.posicao;
        double distancia = vetorDiferenca.comprimento();

        return distancia <= (corpoA.raio + corpoB.raio);
    }

    bool checarLimites(const CorpoRigido &corpoA, double largura, double altura)
    {
        return (
            corpoA.posicao.x - corpoA.raio <= 0 || // tela vai de 0 ->largura(esq ->dir) e 0 -> altura (baixa -> cima)
            corpoA.posicao.x + corpoA.raio >= largura ||
            corpoA.posicao.y - corpoA.raio <= 0 ||
            corpoA.posicao.y + corpoA.raio >= altura);
    }
    void checagem(double largura, double altura)
    {
        for (auto &corpo : corpos)
        {
            if (checarLimites(*corpo, largura, altura))
            {
                corpo->velocidade.x = corpo->velocidade.x * (-1);
                corpo->velocidade.y = corpo->velocidade.y * (-1);
                std::cout << "colisa em x = " << corpo->posicao.x << "| y = " << corpo->posicao.y << std::endl;
            }
        }
        for (size_t i = 0; i < corpos.size(); i++)
        {
            for (size_t j = i + 1; j < corpos.size(); j++)
            {
                if (checarColisao(*corpos[i], *corpos[j]))
                {
                    corpos[i]->velocidade.x = corpos[i]->velocidade.x * (-1);
                    corpos[i]->velocidade.y = corpos[i]->velocidade.y * (-1);
                    corpos[j]->velocidade.x = corpos[j]->velocidade.x * (-1);
                    corpos[j]->velocidade.y = corpos[j]->velocidade.y * (-1);
                    std::cout << "colisao de duas bolas" << std::endl;
                }
            }
        }
    }
};

#endif