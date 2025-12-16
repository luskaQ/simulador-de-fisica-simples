#include <GLFW/glfw3.h>
#include <iostream>
#include "corpoRigido.h"
#include <vector>
#define LARGURA 800
#define ALTURA 600
#define PI 3.14159265359
#define PASSOS 20
#ifndef INTERFACE_H
#define INTERFACE_H

const double angle = PI * 2.0f / PASSOS;

class Interface
{
private:
    GLFWwindow *janela;

public:
    GLFWwindow *getJanela()
    {
        return janela;
    }
    void criaJanela()
    {
        if (!glfwInit())
        {
            std ::cerr << "Erro ao inicializar o glfw";
        }
        else
        {
            janela = glfwCreateWindow(LARGURA, ALTURA, "simulacao", nullptr, nullptr);
            if (!janela)
            {
                std ::cerr << "Erro ao inicializar o janela";
                glfwTerminate();
            }
        }
        glfwMakeContextCurrent(janela);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-1, 1, -1, 1, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void desenhaCirculo(const CorpoRigido &corpo)
    {

        double x = (corpo.posicao.x / LARGURA) * 2.0 - 1.0;
        double y = (corpo.posicao.y / ALTURA) * 2.0 - 1.0;
        double rx = (corpo.raio / LARGURA) *2.0f; // escala simples
        double ry = (corpo.raio / ALTURA) *2.0f; // escala simples

        glBegin(GL_TRIANGLE_FAN);

        glVertex2f(x, y);
        for (int i = 0; i <= PASSOS; i++)
        {
            double ang = i * angle;
            glVertex2f(
                x + cos(ang) * rx,
                y + sin(ang) * ry);
        }
        glEnd();
    }

    void renderizar(const std::vector<CorpoRigido *> &corpos)
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto corpo : corpos)
            desenhaCirculo(*corpo);
    }
};

#endif