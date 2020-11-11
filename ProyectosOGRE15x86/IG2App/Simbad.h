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

	
private:
	Ogre::SceneNode* simbadNode = nullptr;
	AnimationState* animationState;

};
