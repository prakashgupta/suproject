#include "App.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

App::App()
{
    device = createDevice(EDT_OPENGL, dimension2d<u32>(1024, 768), 32, false, false, false, 0);

    driver = device->getVideoDriver();
    smgr = device->getSceneManager();
    guienv = device->getGUIEnvironment();
}

App::~App()
{
    device->drop();
}

void App::createPlayer()
{
    Player* player = new Player(smgr);

    playerVector.push_back(player);
}

void App::loadScenario(stringc file, stringc mapName)
{
    scenario = new Scenario(device, file, mapName);
}

void App::run()
{
    while(device->run())
    {
        driver->beginScene(true, true, SColor(0,0,0,0));

        smgr->drawAll();
        guienv->drawAll();

        driver->endScene();
    }
}


