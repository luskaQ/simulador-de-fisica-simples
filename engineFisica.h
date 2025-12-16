#ifndef ENGINEFISICA_H
#define ENGINEFISICA_H

#include <vector>
#include "corpoRigido.h"
#include <iostream>
const double EPS = 1e-6;
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

        return distancia <= (corpoA.raio + corpoB.raio + EPS);
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
        Vector2 vetor;
        for (auto &corpo : corpos)
        {
            if (checarLimites(*corpo, largura, altura))
            {
                resolverLimites(*corpo, largura, altura);
                resolverColisaoParede(*corpo, largura, altura);
                std::cout << "colisa em x = " << corpo->posicao.x << "| y = " << corpo->posicao.y << std::endl;
            }
        }
        for (size_t i = 0; i < corpos.size(); i++)
        {
            for (size_t j = i + 1; j < corpos.size(); j++)
            {
                if (checarColisao(*corpos[i], *corpos[j]))
                {
                    /*Vector2 diff = corpos[i]->posicao - corpos[j]->posicao;
                    double dist = diff.comprimento();

                    if (dist == 0)
                        return;

                    double sobreposicao = (corpos[i]->raio + corpos[j]->raio) - dist;

                    corpos[i]->posicao += diff * (sobreposicao / 2.0);
                    corpos[j]->posicao -= diff * (sobreposicao / 2.0);*/

                    Vector2 normal = (corpos[i]->posicao - corpos[j]->posicao).normalizado();
                    Vector2 vRel = corpos[i]->velocidade - corpos[j]->velocidade;

                    double vn = Vector2::dot(vRel, normal);
                    if (vn < 0)
                    {
                        Vector2 impulso = normal * (-vn) * 1;
                        corpos[i]->velocidade += impulso;
                        corpos[j]->velocidade -= impulso;
                    }

                    std::cout << "colisao i em x = " << corpos[i]->posicao.x << "| y = " << corpos[i]->posicao.y << std::endl;
                    std::cout << "colisao j em x = " << corpos[j]->posicao.x << "| y = " << corpos[j]->posicao.y << std::endl;
                }
            }
        }
    }
    void resolverLimites(CorpoRigido &corpo, double largura, double altura)
    {
        if (corpo.posicao.x - corpo.raio < 0)
        {
            corpo.posicao.x = corpo.raio;
        }
        else if (corpo.posicao.x + corpo.raio > largura)
        {
            corpo.posicao.x = largura - corpo.raio;
        }

        if (corpo.posicao.y - corpo.raio < 0)
        {
            corpo.posicao.y = corpo.raio;
        }
        else if (corpo.posicao.y + corpo.raio > altura)
        {
            corpo.posicao.y = altura - corpo.raio;
        }
    }
    void resolverColisaoParede(CorpoRigido &corpo, double largura, double altura)
    {
        Vector2 normal;

        if (corpo.posicao.x - corpo.raio <= 0)
            normal = Vector2{1, 0};
        else if (corpo.posicao.x + corpo.raio >= largura)
            normal = Vector2{-1, 0};
        else if (corpo.posicao.y - corpo.raio <= 0)
            normal = Vector2{0, 1};
        else if (corpo.posicao.y + corpo.raio >= altura)
            normal = Vector2{0, -1};
        else
            return;

        double vn = Vector2::dot(corpo.velocidade, normal);

        if (vn < 0)
        {
            corpo.velocidade = corpo.velocidade - normal * (2 * vn);
        }
    }
};

#endif