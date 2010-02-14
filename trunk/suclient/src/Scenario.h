#include <irrlicht.h>

using namespace std;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Scenario
{
	public:
		Scenario(IrrlichtDevice* dev, stringc file, stringc mapName);
		~Scenario();//TODO: remove pk3 from filesystem cache
	private:
        IrrlichtDevice* device;
};

