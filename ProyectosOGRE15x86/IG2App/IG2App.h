#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreCompositorManager.h>

#include "Aspa.h"
#include "Avion.h"
#include "Plano.h"
#include "Simbad.h"
#include "Boya.h"

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
  OgreBites::CameraMan* mCamMgr = nullptr;

  // Escena 1
  Plano* plano = nullptr;
  Plano* plano2 = nullptr;

  Molino* ent_molino = nullptr;
  Avion* avion = nullptr;
  Simbad* simbad=nullptr;
  Boya* boya = nullptr;

  int scene = 1; 
  bool lum_active = false;
  bool blur_active = false;
};

#endif
