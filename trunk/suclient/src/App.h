#include <irrlicht.h>
#include "Player.h"
#include "Scenario.h"
#include <vector>


using namespace std;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class App
{
	public:
		App();
		~App();

        void createPlayer();
        void loadScenario(stringc file, stringc mapName);
		void run();

	private:

        IrrlichtDevice* device;
        IVideoDriver* driver;
        ISceneManager* smgr;
        IGUIEnvironment* guienv;

        vector<Player*> playerVector;

        Scenario* scenario;
};
