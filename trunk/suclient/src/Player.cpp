#include "Player.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

///Loads all objects needed for player entity.
Player::Player(ISceneManager* mgr)
{
    smgr = mgr;

    playerCam = smgr->addCameraSceneNodeFPS(0,100,0.1);

    gunsMeshVector.push_back(smgr->getMesh("../media/gun.b3d"));
    gunNode=smgr->addAnimatedMeshSceneNode(gunsMeshVector[0],playerCam);
}

///CleanUp: delete and clean objects in reverse order they are created.
Player::~Player()
{
    gunNode->remove();

    for (int i=0; i<gunsMeshVector.size(); i++)
    {
        smgr->getMeshCache()->removeMesh((IAnimatedMesh*)gunsMeshVector[i]);
    }

    gunsMeshVector.clear();

    playerCam->remove();
}

///Changes the player active Gun.
void Player::setGun(s32 gunIndex)
{
    if(gunIndex < gunsMeshVector.size())
    {
        gunNode->setMesh( ((IAnimatedMesh*)gunsMeshVector[gunIndex]) );
    }
    else
    {
        cout << "ERROR: Gun index ´´ " << gunIndex << " ´´ does not exist!" << endl;
    }
}
