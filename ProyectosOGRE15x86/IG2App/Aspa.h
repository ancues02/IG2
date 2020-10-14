#pragma once

#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>

using namespace Ogre;
class Aspa : public OgreBites::InputListener
{
public:
    Aspa(Ogre::SceneNode* parentNode);
    ~Aspa();

private:
    Ogre::SceneNode* aspaNode = nullptr;
    Ogre::SceneNode* tableroNode = nullptr;;
    Ogre::SceneNode* cilindroNode = nullptr;
};

