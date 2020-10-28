#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>

#include "Aspa.h"
#include "Avion.h"

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();
  
  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
      
  Ogre::SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  Ogre::SceneNode* mLightNode = nullptr;
  Ogre::SceneNode* mCamNode = nullptr;
  Ogre::SceneNode* mSinbadNode = nullptr;
  Ogre::SceneNode* mEdificioNode = nullptr;

  // Apartado 1
  Ogre::SceneNode* aspaNode = nullptr;
  Ogre::SceneNode* tableroNode = nullptr;;
  Ogre::SceneNode* cilindroNode = nullptr;
  //------
  Ogre::SceneNode* aspas = nullptr;
  Ogre::SceneNode* numAspas[12];
  AspasMolino* molino = nullptr;
    // Escena 0, 12, 13
  Ogre::SceneNode* Clock = nullptr;
  Ogre::SceneNode* mHourNode[12];
  Ogre::SceneNode* mAgujas[3];
  Ogre::SceneNode* spheresParent = nullptr;
  Ogre::SceneNode* segundosParent = nullptr;

  Molino* molino_Completo = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;

  //Escena 14, 15
  Ogre::SceneNode* Sol = nullptr;
  Ogre::SceneNode* Tierra = nullptr;
  Ogre::Vector3 posIni = { 0,0,0 };
  Ogre::SceneNode* Luna = nullptr;

  //Escena 16,17
  Avion* avion = nullptr;

  int rad = 500;
  int scene = 18;
 
};

#endif
