#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>
#include <OgreFrameListener.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <SDL_keycode.h>

#include "Messages.h"

using namespace Ogre;

class EntidadIG :public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(SceneNode* node);
	virtual ~EntidadIG() {}
	//Vector estático de listeners
	static std::vector<EntidadIG*> appListeners;
	//Añadir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad);

	virtual void frameRendered(const Ogre::FrameEvent& evt) {};

	void sendEvent(msg::MessageType msgType, EntidadIG* entidad);
	virtual void receiveEvent(msg::MessageType msgType, EntidadIG* entidad) {};

protected:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneManager* mSM = nullptr;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};