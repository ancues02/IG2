#pragma once
#include "Aspa.h"

using namespace Ogre;
class Avion : public EntidadIG
{
public:
    Avion(Ogre::SceneNode* parentNode);
    virtual ~Avion();
    //virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void frameRendered(const Ogre::FrameEvent& evt);
    virtual void receiveEvent(msg::MessageType msgType, EntidadIG* entidad);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

    AspasMolino* getHeliceDer(){
		return helice_D;
	}

    AspasMolino* getHeliceIzq(){
		return helice_I;
	}

private:
    Ogre::SceneNode* avionNode = nullptr;
    Ogre::SceneNode* cuerpoNode = nullptr;
    Ogre::SceneNode* alaINode = nullptr;
    Ogre::SceneNode* alaDNode = nullptr;
	Ogre::SceneNode* frenteNode = nullptr;
    Ogre::SceneNode* pilotoNode = nullptr;

    AspasMolino* helice_D = nullptr;
	AspasMolino* helice_I = nullptr;
    static int cont;
    Vector3 posIni;
    
	//luz
    Ogre::SceneNode* lightNode = nullptr;
    Light* luzFoco = nullptr;

	bool move_avion = true;

    // Billboards
    BillboardSet* bbSet = nullptr;
    // Particle Systems
    ParticleSystem* pSys = nullptr;
    
    //Ogre::SceneNode* bbNode = nullptr;
};
