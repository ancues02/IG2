#pragma once
#include "EntidadIG.h"
using namespace Ogre;

class Simbad : public EntidadIG
{
public:
	Simbad(Ogre::SceneNode* parentNode);
	~Simbad();
	virtual void receiveEvent(msg::MessageType msgType, EntidadIG* entidad);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	
private:
	Ogre::SceneNode* simbadNode = nullptr;
	Ogre::Entity* simbadEnt = nullptr;
	Ogre::Entity* sword;
	AnimationState* animationState;
	AnimationState* as_runTop;
	AnimationState* as_runBot;

	bool dance=true;
	bool dcha = true;
};
