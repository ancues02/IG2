#pragma once
#include "EntidadIG.h"
class Plano : public EntidadIG
{
public:
    Plano(Ogre::SceneNode* parentNode);
    virtual ~Plano();
    virtual void receiveEvent(msg::MessageType msgType, EntidadIG* entidad);
    int getID() {
        return id;
    }
	void setMaterial(std::string name);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

private:
	Ogre::Entity* plane;
    static int cont;
	Ogre::SceneNode* planoNode = nullptr;
    int id;
};

