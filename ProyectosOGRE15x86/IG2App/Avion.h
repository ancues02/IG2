#pragma once

#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

#include <SDL_keycode.h>
#include "Aspa.h"
using namespace Ogre;
class Avion : public OgreBites::InputListener
{
public:
    Avion(Ogre::SceneNode* parentNode);
    ~Avion();
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
    Ogre::SceneNode* mNode = nullptr;
    Ogre::SceneNode* cuerpoNode = nullptr;
    Ogre::SceneNode* alaINode = nullptr;;
    Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* frenteNode = nullptr;;
    Ogre::SceneNode* pilotoNode = nullptr;;
    AspasMolino* heliceNode_D = nullptr;;
	AspasMolino* heliceNode_I = nullptr;
    static int cont;
};
