#pragma once

#include <OgreInput.h>
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreEntity.h>

#include <SDL_keycode.h>

using namespace Ogre;
class Aspa : public OgreBites::InputListener
{
public:
    Aspa(Ogre::SceneNode* parentNode);
    ~Aspa();
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	//Ogre::SceneManager* mSM = nullptr;

    Ogre::SceneNode* aspaNode = nullptr;
    Ogre::SceneNode* tableroNode = nullptr;;
    Ogre::SceneNode* cilindroNode = nullptr;
    static int cont;
};

class AspasMolino : public OgreBites::InputListener 
{
public:
    AspasMolino(Ogre::SceneNode* parentNode, int nAspas);
    ~AspasMolino();
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
    Ogre::SceneNode* aspasNode = nullptr;
    int numAspas;
    Aspa** arrayAspas;
    Ogre::SceneNode* centroNode = nullptr;
};

class Molino : public OgreBites::InputListener
{
public:
    Molino(Ogre::SceneNode* parentNode, int nAspas);
    ~Molino();
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
private:
    Ogre::SceneNode* esfera = nullptr;
    Ogre::SceneNode* cilCuerpo = nullptr;
    AspasMolino* aspasMolino = nullptr;
};

