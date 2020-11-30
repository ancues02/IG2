#pragma once
#include "EntidadIG.h"
#include <OgreMeshManager.h>
#include <OgreMovablePlane.h>
#include <OgreCamera.h>
#include <OgreTextureManager.h>
#include <OgreRenderTexture.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreViewport.h>
#include <OgreSubEntity.h>
#include <OgreTechnique.h>
#include <OgreRenderTargetListener.h>

class Plano : public EntidadIG, public RenderTargetListener
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
    void setReflejo(Camera* camRef);

    // RenderTargetListener

    //virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
    //virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
private:
	Ogre::Entity* plane;
    static int cont;
	Ogre::SceneNode* planoNode = nullptr;
    int id;
    MovablePlane* mpRef = nullptr;
};

