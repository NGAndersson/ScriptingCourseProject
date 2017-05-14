#include <irrlicht.h>
#include <lua.h>
#include "LuaHandler.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

int main()
{
	IrrlichtDevice *device =
		createDevice(video::EDT_OPENGL, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);

	if (!device)
		return 1;

	device->setWindowCaption(L"Scripting Project");
	
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	guienv->addStaticText(L"TEST TEXT!", rect<s32>(10, 10, 260, 22), true);
	IAnimatedMesh* mesh = smgr->getMesh("media/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);

	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("media/sydney.bmp"));
	}

	smgr->addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));

	//Quake3 map
	device->getFileSystem()->addFileArchive("media/map-20kdm2.pk3");
	IAnimatedMesh* mapMesh = smgr->getMesh("20kdm2.bsp");
	ISceneNode* mapNode = 0;
	if (mapMesh)
		mapNode = smgr->addOctreeSceneNode(mapMesh->getMesh(0), 0, -1, 1024);

	if (mapNode)
		mapNode->setPosition(core::vector3df(-1300, -144, -1249));
	

	//Camera
	smgr->addCameraSceneNodeFPS();
	device->getCursorControl()->setVisible(false);

	LuaHandler* luaHandler = new LuaHandler;

	while (device->run())
	{

		luaHandler->Update();
		if (device->isWindowActive())
		{
			driver->beginScene(true, true, SColor(255, 100, 101, 140));
			smgr->drawAll();
			guienv->drawAll();
			driver->endScene();
		}
		else
		{
			device->yield();
		}
	}
	
	device->drop();
	return 0;
}