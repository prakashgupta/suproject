#include <irrlicht.h>
#include <iostream>
#include <vector>

using namespace std;

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

class Player
{
	public:
		Player(ISceneManager* mgr);
		~Player();

		void setGun(s32 gunIndex);
	private:
        ISceneManager* smgr;
        ICameraSceneNode* playerCam;

        vector<IAnimatedMesh*> gunsMeshVector;
        IAnimatedMeshSceneNode* gunNode;
};

