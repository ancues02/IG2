#pragma once

#include "EntidadIG.h"

using namespace Ogre;
class Aspa : public EntidadIG
{
public:
    Aspa(Ogre::SceneNode* parentNode);
    ~Aspa();
    int getAspaID(){
        return id;
    }
private:
	
    Ogre::SceneNode* aspaNode = nullptr;
    Ogre::SceneNode* tableroNode = nullptr;;
    Ogre::SceneNode* cilindroNode = nullptr;
    static int cont;
    int id;
};

class AspasMolino : public EntidadIG
{
public:
    AspasMolino(Ogre::SceneNode* parentNode, int nAspas);
    ~AspasMolino();
    virtual void receiveEvent(msg::MessageType msgType, EntidadIG* entidad);
    int getID() {
        return id;
    }
	Aspa** getAspasArray() const {
		return arrayAspas;
	}
	int getNumAspas() const { return numAspas; }

private:
    Ogre::SceneNode* aspasNode = nullptr;
    int numAspas;
    Aspa** arrayAspas;
    Ogre::SceneNode* centroNode = nullptr;
    static int cont; 
    int id;
};

class Molino : public EntidadIG
{
public:
    Molino(Ogre::SceneNode* parentNode, int nAspas);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

    ~Molino();
    virtual void receiveEvent(msg::MessageType msgType, EntidadIG* entidad);
private:
    Ogre::SceneNode* molinoNode = nullptr;
    Ogre::SceneNode* esfera = nullptr;
    Ogre::SceneNode* cilCuerpo = nullptr;
    Ogre::SceneNode* ficticio = nullptr;
    int numAspas;
    Vector3 posIni;
    AspasMolino* aspasMolino = nullptr;
};

