#include "src/App.h"

int main(int argc, char** argv)
{
    App* app=new App();

    app->createPlayer();

    //app->loadScenario("../media/map.pk3", "abdm1.bsp");
    app->loadScenario("../media/sp123.pk3", "sp123.bsp");

    app->run();

    delete app;

    return 0;
}
