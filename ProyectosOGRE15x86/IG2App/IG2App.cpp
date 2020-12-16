#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include <iostream>
using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_ESCAPE)
    {
        getRoot()->queueEndRendering();
    }  
	else if (evt.keysym.sym == SDLK_l) {
		lum_active = !lum_active;
		CompositorManager::getSingleton().setCompositorEnabled(getRenderWindow()->getViewport(0), "IG2/Luminance", lum_active);
	}
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
	vp->setBackgroundColour(Ogre::ColourValue(0.0, 0.0, 0.0));//cambia el color del fondo

	// Compositors
	CompositorManager::getSingleton().addCompositor(vp, "IG2/Luminance");
	//------------------------------------------------------------------------

	// without light we would just get a black screen 

	Light* luz = mSM->createLight("Luz");
	luz->setType(Ogre::Light::LT_DIRECTIONAL);
	luz->setDiffuseColour(0.75, 0.75, 0.75);

	mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
	//mLightNode = mCamNode->createChildSceneNode("nLuz");
	mLightNode->attachObject(luz);

	mLightNode->setDirection(Ogre::Vector3(0, -1, -1));  //vec3.normalise();

	//lightNode->setPosition(0, 0, 1000);

	// SkyPlane
	//mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -200), "IG2App/space", 1, 1, true, 0.0, 10, 10);
	mSM->setSkyPlane(true, Plane(Vector3::UNIT_Z, -20), "IG2/spaceGLSL", 1, 1, true, 1.0, 10, 10);

	
	//------------------------------------------------------------------------
	if (scene == 1) {
		plano = new Plano(mSM->getRootSceneNode());
		plano->setMaterial("IG2App/reflejo");
		
		plano->setReflejo(cam);

		addInputListener(plano);
		EntidadIG::addListener(plano);

		plano2 = new Plano(mSM->getRootSceneNode());
		plano2->setMaterial("Practica1/naranjete");

		ent_molino = new Molino(mSM->getRootSceneNode(), 6);
		addInputListener(ent_molino);//para eventos de teclado
		EntidadIG::addListener(ent_molino);//para recibir mensajes entre entidades

		addInputListener(ent_molino->getAspas());//para eventos de teclado
		EntidadIG::addListener(ent_molino->getAspas());//para recibir mensajes entre entidades
		
		//añadimos al avion y sus helices como listeners tanto de teclado como de mensajes(receive)
		avion = new Avion(mSM->getRootSceneNode());
		addInputListener(avion);
		EntidadIG::addListener(avion);

		addInputListener(avion->getHeliceDer());
		EntidadIG::addListener(avion->getHeliceDer());

		addInputListener(avion->getHeliceIzq());
		EntidadIG::addListener(avion->getHeliceIzq());


		simbad = new Simbad(mSM->getRootSceneNode());
		addInputListener(simbad);//para eventos de teclado
		EntidadIG::addListener(simbad);//para recibir mensajes entre entidades

		boya = new Boya(mSM->getRootSceneNode());
		addInputListener(boya);


		mSM->getSceneNode("plano_1")->scale(2, 2, 2);
		mSM->getSceneNode("plano_2")->translate(860, 1, -630);//plano debajo del molino
		mSM->getSceneNode("plano_2")->scale(0.4, 0.4, 0.4);
		mSM->getSceneNode("molino")->translate(860, 300, -630);
		
		Ogre::SceneNode* esfera = nullptr;
		esfera = mSM->getRootSceneNode()->createChildSceneNode("cara");
		Ogre::Entity* ent = mSM->createEntity("sphere.mesh");
		ent->setMaterialName("Practica1/cara");
		esfera->attachObject(ent);
		esfera->setScale(0.2, 0.2, 0.2);
		esfera->translate(1000, 20, -550);

		//mSM->createAnimationState()
	}
	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------

}
