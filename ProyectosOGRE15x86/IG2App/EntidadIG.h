/*#pragma once
#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

#include <SDL_keycode.h>
using namespace Ogre;

class EntidadIG :public OgreBites::InputListener {
public:
	//Constructora y destructora
	EntidadIG(SceneNode* node, ...);
	~EntidadIG() {}
	//Vector est�tico de listeners
	static std::vector<EntidadIG*> appListeners;
	//A�adir entidad como listener al vector con push_back()
	static void addListener(EntidadIG* entidad);
protected:
	Ogre::SceneNode* mNode = nullptr;
	Ogre::SceneManager* mSM = nullptr;
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
};*/