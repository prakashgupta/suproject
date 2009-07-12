#include <irrlicht/irrlicht.h>
#include <iostream>
#define PI 3.14159265

using namespace irr;

class MyEventReceiver : public IEventReceiver
{
public:
  virtual bool OnEvent(const SEvent& event)
  {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
      //      for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
      //	KeyIsDown[i] = false;
      KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    
    if (event.EventType == irr::EET_MOUSE_INPUT_EVENT) {
      for (u32 i=0; i<EMIE_COUNT; i++)
	MouseIsDown[i] = false;
      MouseIsDown[event.MouseInput.Event] = true;
    }
    
    return false;
  }
  
  virtual bool IsKeyDown(EKEY_CODE keyCode) const
  {
    return KeyIsDown[keyCode];
  }
  
  virtual bool IsMouseDown(EMOUSE_INPUT_EVENT mouseCode) const
  {
    return MouseIsDown[mouseCode];
  }
  
  MyEventReceiver()
  {
    for (u32 i=0; i<KEY_KEY_CODES_COUNT; ++i)
      KeyIsDown[i] = false;
    
    for (u32 i=0; i<EMIE_COUNT; i++)
      MouseIsDown[i] = false;
  }
  
private:
  bool KeyIsDown[KEY_KEY_CODES_COUNT];
  //  bool KeyIsLeft[KEY_KEY_CODES_COUNT];
  bool MouseIsDown[EMIE_COUNT];
};


int main() {
  
  MyEventReceiver receiver;
  
  IrrlichtDevice *device = createDevice(video::EDT_OPENGL, core::dimension2d<s32>(1024, 768), 16, false, false, false, &receiver);
  
  SKeyMap keyMap[9];
  keyMap[0].Action = EKA_MOVE_FORWARD;
  keyMap[0].KeyCode = KEY_UP;
  keyMap[1].Action = EKA_MOVE_FORWARD;
  keyMap[1].KeyCode = KEY_KEY_W;
  
  keyMap[2].Action = EKA_MOVE_BACKWARD;
  keyMap[2].KeyCode = KEY_DOWN;
  keyMap[3].Action = EKA_MOVE_BACKWARD;
  keyMap[3].KeyCode = KEY_KEY_S;
  
  keyMap[4].Action = EKA_STRAFE_LEFT;
  keyMap[4].KeyCode = KEY_LEFT;
  keyMap[5].Action = EKA_STRAFE_LEFT;
  keyMap[5].KeyCode = KEY_KEY_A;
  
  keyMap[6].Action = EKA_STRAFE_RIGHT;
  keyMap[6].KeyCode = KEY_RIGHT;
  keyMap[7].Action = EKA_STRAFE_RIGHT;
  keyMap[7].KeyCode = KEY_KEY_D;
  
  keyMap[8].Action = EKA_JUMP_UP;
  keyMap[8].KeyCode = KEY_SPACE;
  
  
  if (device == 0)
    return 1;
  
  
  video::IVideoDriver* driver = device->getVideoDriver();
  scene::ISceneManager* smgr = device->getSceneManager();
  
  device->getFileSystem()->addZipFileArchive("./map-20kdm2.pk3");
  
  scene::IAnimatedMesh* q3levelmesh = smgr->getMesh("20kdm2.bsp");
  scene::ISceneNode* q3node = 0;
  
  if (q3levelmesh)
    q3node = smgr->addOctTreeSceneNode(q3levelmesh->getMesh(0));
  
  scene::ITriangleSelector* selector = 0;
  
  if (q3node)
    {
      q3node->setPosition(core::vector3df(-1350,-130,-1400));
      
      selector = smgr->createOctTreeTriangleSelector(q3levelmesh->getMesh(0), q3node, 128);
      q3node->setTriangleSelector(selector);
    }
  
  
  scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0, 100.0f, .3f, -1, keyMap, 9, false, 2.0f);
  
  camera->setPosition(core::vector3df(-100,50,-150));
  
  device->getCursorControl()->setVisible(false);
  
  
  if (selector)
    {
      scene::ISceneNodeAnimator* anim =
	smgr->createCollisionResponseAnimator(
					      selector, camera, core::vector3df(30,50,30),
					      core::vector3df(0,-10,0),
					      core::vector3df(0,50,0));
      camera->addAnimator(anim);
      anim->drop();
    }
  scene::ISceneNode* selectedSceneNode = 0;
  scene::ISceneNode* lastSelectedSceneNode = 0;
  
  
    scene::IAnimatedMesh* sydney_mesh = smgr->getMesh("./sydney.md2");
  if (!sydney_mesh)
    return 1;
  scene::IAnimatedMeshSceneNode* sydney_node = smgr->addAnimatedMeshSceneNode(sydney_mesh);
  
  
  if (sydney_node)
    {
      sydney_node->setMaterialFlag(video::EMF_LIGHTING, false);
      sydney_node->setMD2Animation(scene::EMAT_STAND);
      //sydney_node->setFrameLoop(0, 0);
      //      sydney_node->setAnimationSpeed(15);
		
      sydney_node->setMaterialTexture( 0, driver->getTexture("./sydney.bmp") );
    }
  
  
  int lastFPS = -1;
  
  while(device->run())
    if (device->isWindowActive())
      {
	driver->beginScene(true, true, 0);
	
	smgr->drawAll();
	
	core::line3d<f32> line;
	line.start = camera->getPosition();
	line.end = line.start + (camera->getTarget() - line.start).normalize() * 1000.0f;
	
	core::vector3df intersection;
	core::triangle3df tri;
	
	if (smgr->getSceneCollisionManager()->getCollisionPoint(line, selector, intersection, tri))
	  {
	    driver->setTransform(video::ETS_WORLD, core::matrix4());
	    //	    driver->setMaterial(material);
	    //	    driver->draw3DTriangle(tri, video::SColor(0,255,0,0));
	  }
	selectedSceneNode = smgr->getSceneCollisionManager()->getSceneNodeFromCameraBB(camera);
	
	if (lastSelectedSceneNode)
	  lastSelectedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
	
	if (selectedSceneNode)
	  selectedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
	
	lastSelectedSceneNode = selectedSceneNode;
 

	if(receiver.IsKeyDown(irr::KEY_LSHIFT) || receiver.IsMouseDown(irr::EMIE_LMOUSE_PRESSED_DOWN)) {
	core::position2d<s32> m = device->getCursorControl()->getPosition();
	  	  driver->draw2DRectangle(video::SColor(255,255,0,0),
		  core::rect<s32>(m.X-5, m.Y-5, m.X+5, m.Y+5));
	  
  	}

	if(receiver.IsKeyDown(irr::KEY_KEY_W) || receiver.IsKeyDown(irr::KEY_KEY_S))
	  sydney_node->setMD2Animation(scene::EMAT_RUN);
	else
	  sydney_node->setMD2Animation(scene::EMAT_STAND);

	core::vector3df cposition = camera->getPosition(), crotation = camera->getRotation(),srotation = sydney_node->getRotation();

	sydney_node->setPosition(core::vector3df(cposition.X, cposition.Y-28, cposition.Z));
	driver->endScene();

		sydney_node->setRotation(core::vector3df(srotation.X, crotation.Y-90, srotation.Z));

	int fps = driver->getFPS();
	
	if (lastFPS != fps)
	  {
	    core::stringw str = L"Irrlicht Engine [";
	    str += driver->getName();
	    str += "] FPS:";
	    str += fps;
	    
	    device->setWindowCaption(str.c_str());
	    lastFPS = fps;
	  }
      }
  
  selector->drop();
  device->drop();
  
  return 0;
}
