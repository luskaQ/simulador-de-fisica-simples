#include "interface.h"
#include "engineFisica.h"
int main()
{
    EngineFisica engine;
    Interface interface;

    CorpoRigido c1(Vector2(LARGURA / 2, ALTURA/2 - 200), Vector2(-200, 200.0f), 50.0f, 1.0f);
    CorpoRigido c2(Vector2(LARGURA / 2, ALTURA/2 + 200), Vector2(200, -200.0f), 50.0f, 1.0f);

    engine.adicionarCorpo(&c1);
    engine.adicionarCorpo(&c2);

    interface.criaJanela();

    double lastTime = glfwGetTime();

    while (!glfwWindowShouldClose(interface.getJanela()))
    {
        double currentTime = glfwGetTime();
        double delta = currentTime - lastTime;
        lastTime = currentTime;
        engine.checagem(LARGURA, ALTURA);
        engine.atualizar(delta);

        interface.renderizar(engine.getCorpos());

        glfwSwapBuffers(interface.getJanela());
        glfwPollEvents();
    }
}