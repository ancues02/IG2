#pragma once


#include "Aspa.h"

using namespace Ogre;
class Avion : public EntidadIG
{
public:
    Avion(Ogre::SceneNode* parentNode);
    ~Avion();
    //virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual void receiveEvent(msg::MessageType msgType, EntidadIG* entidad);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
    Ogre::SceneNode* avionNode = nullptr;
    Ogre::SceneNode* cuerpoNode = nullptr;
    Ogre::SceneNode* alaINode = nullptr;
    Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* frenteNode = nullptr;
    Ogre::SceneNode* pilotoNode = nullptr;
    AspasMolino* heliceNode_D = nullptr;
	AspasMolino* heliceNode_I = nullptr;
    static int cont;
    Vector3 posIni;

	//luz
    Ogre::SceneNode* lightNode = nullptr;
    Light* luzFoco = nullptr;

	bool move_avion = true;

};
