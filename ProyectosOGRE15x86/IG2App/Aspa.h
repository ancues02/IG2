#pragma once

#include "EntidadIG.h"

using namespace Ogre;
class Aspa : public EntidadIG
{
public:
    Aspa(Ogre::SceneNode* parentNode);
    virtual ~Aspa();
    int getAspaID(){
        return id;
    }
	
    Entity* getAdorno_ent(){
		return cilindro_ent;
	}
private:
	
    Ogre::SceneNode* aspaNode = nullptr;
    Ogre::SceneNode* tableroNode = nullptr;;
    Ogre::SceneNode* cilindroNode = nullptr;
	Ogre::Entity* cilindro_ent = nullptr;
    static int cont;    // Cuenta todas las aspas
    int id;             // El identificador de cada aspa, para poder acceder a ellas ya que accedemos a traves del nombre (no hay getters de los nodos)
};

class AspasMolino : public EntidadIG
{
public:
    AspasMolino(Ogre::SceneNode* parentNode, int nAspas);
    virtual ~AspasMolino();
    virtual void receiveEvent(msg::MessageType msgType, EntidadIG* entidad);
    int getID() {
        return id;
    }
	Aspa** getAspasArray() const {
		return arrayAspas;
	}
     Ogre::SceneNode* getAspasNode(){
		return aspasNode;
	}
    Ogre::SceneNode* getCentroNode(){
		return centroNode;
	}
	int getNumAspas() const { return numAspas; }
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
    Ogre::SceneNode* aspasNode = nullptr;
    int numAspas;
    Aspa** arrayAspas;
    Ogre::SceneNode* centroNode = nullptr;
    static int cont;        // Cuenta todas las aspasMolino
    int id;                 // El identificador de cada aspasMolino, para poder acceder a ellas ya que accedemos a traves del nombre (no hay getters de los nodos)
	bool gira = true;
};

class Molino : public EntidadIG
{
public:
    Molino(Ogre::SceneNode* parentNode, int nAspas);
	virtual void frameRendered(const Ogre::FrameEvent& evt);

    virtual ~Molino();
    virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
    virtual void receiveEvent(msg::MessageType msgType, EntidadIG* entidad);
	AspasMolino* getAspas() {
		return  aspasMolino;
	}
private:
    Ogre::SceneNode* molinoNode = nullptr;
    Ogre::SceneNode* esfera = nullptr;
    Ogre::SceneNode* cilCuerpo = nullptr;
    Ogre::SceneNode* ficticio = nullptr;
	Ogre::Entity* esfera_ent = nullptr;
    int numAspas;
    Vector3 posIni;
    AspasMolino* aspasMolino = nullptr;
	bool gira = true;
};

