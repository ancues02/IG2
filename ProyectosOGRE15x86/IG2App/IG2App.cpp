#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }
    //Apartado 3
    else if (evt.keysym.sym == SDLK_g) {
        for (int i = 0; i < 12; i++) {
            numAspas[i]->getChild("adorno_" + std::to_string(i + 1))->roll(Ogre::Degree(10.0f));
        }
        aspas->roll(Ogre::Degree(-10.0f));
    }
    //else if (evt.keysym.sym == SDLK_0) scene = 0;
   // else if (evt.keysym.sym == SDLK_1) scene = 1;
  
  return true;
}

void IG2App::shutdown()
 {
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  vp->setBackgroundColour(Ogre::ColourValue(0.7,0.8,0.9));//cambia el color del fondo

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  //mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render
  //if (scene == 0) {
     /* Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

      mSinbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSinbad");
      mSinbadNode->attachObject(ent);

      mSinbadNode->setPosition(0, 20, 0);
      mSinbadNode->setScale(20, 20, 20);
      //mSinbadNode->yaw(Ogre::Degree(-45));
      //mSinbadNode->showBoundingBox(true);
      //mSinbadNode->setVisible(false);
      Ogre::Entity* ent2 = mSM->createEntity("RomanBathUpper.mesh");

      mEdificioNode = mSM->getRootSceneNode()->createChildSceneNode("edificio");
      mEdificioNode->attachObject(ent2);
      Ogre::Entity* ent3 = mSM->createEntity("RomanBathLower.mesh");
      mEdificioNode->attachObject(ent3);
      //Columns.mesh
      Ogre::Entity* ent4 = mSM->createEntity("Columns.mesh");
      mEdificioNode->attachObject(ent4);*/

      //Esferas reloj

      //mEsferasNode = mSM->getRootSceneNode()->createChildSceneNode("esferas");
  //std::to_string(i)
    //Clock = mSM->getRootSceneNode()->createChildSceneNode("Reloj");
    //spheresParent = Clock->createChildSceneNode("Esferas");
    //int nEsferas = 12;
    //for (int i = 0; i < nEsferas; i++) {
    //    Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
    //    mHourNode[i] = spheresParent->createChildSceneNode("Hora " + std::to_string(i + 1));

    //    mHourNode[i]->attachObject(sphere);
    //    mHourNode[i]->setPosition(Ogre::Math::Cos(Ogre::Degree(i * 360.0 / (float)nEsferas)) * rad, Ogre::Math::Sin(Ogre::Degree(i * 360.0 / (float)nEsferas)) * rad, 0.0);

    //    //Rotar accediendo mediante el nodo
    //    /*if (i % 2 == 0){
    //        Ogre::SceneNode* hora = mSM->getSceneNode("Hora " + std::to_string(i + 1));
    //        hora->setScale(0.5, 0.5, 0.5);
    //    }*/
    //}
    //// Agujas del reloj
   
    //for (int i = 0; i < 3; i++) {
    //    Ogre::Entity* aguja = mSM->createEntity("cube.mesh");
    //    mAgujas[i] = Clock->createChildSceneNode("Aguja " + std::to_string(i + 1));
    //    mAgujas[i]->attachObject(aguja);

    //    mAgujas[i]->setScale(0.2/(i+1), 4, 0.1);


    //}
    //Ogre::SceneNode* agujaHora = mSM->getSceneNode("Aguja 1");
    //agujaHora->setPosition(150, 5, 0);
    //agujaHora->roll(Ogre::Degree(-90));
    //Ogre::SceneNode* agujaMin = mSM->getSceneNode("Aguja 2");
    //agujaMin->setPosition(0, 150, 0);
    //Ogre::SceneNode* agujaSec = mSM->getSceneNode("Aguja 3");
    //agujaSec->setPosition(-150, -80, 0);
    //agujaSec->roll(Ogre::Degree(-240));
    ////agujaSec->setPosition(0, -100, 0);
    ////agujaSec->roll(Ogre::Degree(-180));
 

   // Apartado 1
  //aspaNode = mSM->getRootSceneNode()->createChildSceneNode("aspa");
  //tableroNode = aspaNode->createChildSceneNode("tablero");
  //cilindroNode = aspaNode->createChildSceneNode("adorno");

  //Ogre::Entity* ent = mSM->createEntity("cube.mesh");
  //tableroNode->attachObject(ent);
  //tableroNode->setScale(5, 1, 0.1);
  //
  //ent = mSM->createEntity("Barrel.mesh");
  //cilindroNode->attachObject(ent);
  //cilindroNode->setScale(5, 10,5);
  //cilindroNode->setPosition(150, 0, 20);
  //

  /*for (int i = 0; i < 1; i++) {
	      Ogre::Entity* aguja = mSM->createEntity("cube.mesh");
	      mAgujas[i] = mSM->getRootSceneNode()->createChildSceneNode("Aguja " + std::to_string(i + 1));
	      mAgujas[i]->attachObject(aguja);

	      mAgujas[i]->setScale(1, 5, 0.1);


  }*/
  // Apartado 2
  aspas = mSM->getRootSceneNode()->createChildSceneNode("aspas");
  for (int i = 0; i < 12; i++) {
      numAspas[i] = aspas->createChildSceneNode("aspa_" + std::to_string(i + 1));
      Ogre::SceneNode* tablero = numAspas[i]->createChildSceneNode("tablero_" + std::to_string(i + 1));
      Ogre::Entity* ent = mSM->createEntity("cube.mesh");
      tablero->attachObject(ent);
      tablero->setScale(5, 1, 0.1);
      

      Ogre::SceneNode* adorno = numAspas[i]->createChildSceneNode("adorno_" + std::to_string(i + 1));
      ent = mSM->createEntity("Barrel.mesh");
      adorno->attachObject(ent);
      adorno->setScale(5, 10,5);
      adorno->setPosition(150, 0, 20);
      float rotation = (360.0f / 12.0f) * i;
      numAspas[i]->roll(Ogre::Degree(rotation), Ogre::Node::TS_PARENT);
      numAspas[i]->translate(200, 0, 0, Ogre::Node::TS_LOCAL);
      adorno->roll(Ogre::Degree(-rotation));
  }
      //------------------------------------------------------------------------
 
  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

