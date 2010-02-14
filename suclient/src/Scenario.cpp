#include "Scenario.h"

using namespace std;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

Scenario::Scenario(IrrlichtDevice* dev, stringc file, stringc mapName)
{
    device = dev;

    device->getFileSystem()->addZipFileArchive(file.c_str());

    IAnimatedMesh* mesh = device->getSceneManager()->getMesh(mapName.c_str());

    ISceneNode* node = device->getSceneManager()->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);

}
