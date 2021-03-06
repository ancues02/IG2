#pragma once


#include "EntidadIG.h"

class Boya : public EntidadIG
{
public:
	Boya(Ogre::SceneNode* parentNode);
	virtual void frameRendered(const Ogre::FrameEvent& evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
	virtual ~Boya();
private:
	Ogre::SceneNode* bCilindro = nullptr;
	Ogre::Entity* bEnt = nullptr;
	AnimationState * animationState = nullptr;

	float long_desp = 100.0f;
};

