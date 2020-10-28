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

    //Apartado 3
    else if (evt.keysym.sym == SDLK_g && scene==3) {
        for (int i = 0; i < 12; i++) {
            numAspas[i]->getChild("adorno_" + std::to_string(i + 1))->roll(Ogre::Degree(10.0f));
        }
        aspas->roll(Ogre::Degree(-10.0f));
    }
	//apartado13
    else if (evt.keysym.sym == SDLK_h && scene == 12) {
        Clock->getChild("segundos_Parent")->roll(Ogre::Degree(-10.0f),Ogre::Node::TS_PARENT);
       
    }
	//apartado 14, 15
	else if (evt.keysym.sym == SDLK_j && scene == 14) {
		//rotamos Tierra
		Tierra->translate(-posIni, Ogre::Node::TS_LOCAL);
		Tierra->yaw(Ogre::Degree(-10.0f), Ogre::Node::TS_PARENT);
		Tierra->translate(posIni, Ogre::Node::TS_LOCAL);
		//rotamos nodo fictio de la luna
		Tierra->getChild("LunaParent")->yaw(Ogre::Degree(-10.0f), Ogre::Node::TS_PARENT);

	}
  
  return true;
}

void IG2App::shutdown()
 {
    delete molino;
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
	vp->setBackgroundColour(Ogre::ColourValue(0.7, 0.8, 0.9));//cambia el color del fondo

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
	if (scene == 1) {
		// Apartado 1
		aspaNode = mSM->getRootSceneNode()->createChildSceneNode("aspa");
		tableroNode = aspaNode->createChildSceneNode("tablero");
		cilindroNode = aspaNode->createChildSceneNode("adorno");

		Ogre::Entity* ent = mSM->createEntity("cube.mesh");
		tableroNode->attachObject(ent);
		tableroNode->setScale(5, 1, 0.1);

		ent = mSM->createEntity("Barrel.mesh");
		cilindroNode->attachObject(ent);
		cilindroNode->setScale(5, 10, 5);
		cilindroNode->setPosition(150, 0, 20);


		for (int i = 0; i < 1; i++) {
			Ogre::Entity* aguja = mSM->createEntity("cube.mesh");
			mAgujas[i] = mSM->getRootSceneNode()->createChildSceneNode("Aguja " + std::to_string(i + 1));
			mAgujas[i]->attachObject(aguja);

			mAgujas[i]->setScale(1, 5, 0.1);


		}
	}

	// Apartado 2
	else if (scene == 2) {
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
			adorno->setScale(5, 10, 5);
			adorno->setPosition(150, 0, 20);
			float rotation = (360.0f / 12.0f) * i;
			numAspas[i]->roll(Ogre::Degree(rotation), Ogre::Node::TS_PARENT);
			numAspas[i]->translate(200, 0, 0, Ogre::Node::TS_LOCAL);
			adorno->roll(Ogre::Degree(-rotation));
		}
	}
	// Apartado 4
	else if (scene == 4) {
		Aspa* aspa = new Aspa(mSM->getRootSceneNode());
	}
	// Apartados 5 y 7
	else if (scene == 5 || scene == 7) {

		molino = new AspasMolino(mSM->getRootSceneNode(), 12);
		addInputListener(molino);
	}
	//apartados 9, 10 y 11
	else if (scene == 9) {
		//molino_Completo = new Molino(mSM->getRootSceneNode(), 6);
		ent_molino = new AspasMolino(mSM->getRootSceneNode(), 6);
		//addInputListener(molino_Completo);
	}
	//-------------------------------------------------------------------

	//apartados 12 y 13
	else if (scene == 12) {
		Clock = mSM->getRootSceneNode()->createChildSceneNode("Reloj");
		spheresParent = Clock->createChildSceneNode("Esferas");
		int nEsferas = 12;
		for (int i = 0; i < nEsferas; i++) {
			Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
			mHourNode[i] = spheresParent->createChildSceneNode("Hora " + std::to_string(i + 1));

			mHourNode[i]->attachObject(sphere);
			mHourNode[i]->setPosition(Ogre::Math::Cos(Ogre::Degree(i * 360.0 / (float)nEsferas)) * rad, Ogre::Math::Sin(Ogre::Degree(i * 360.0 / (float)nEsferas)) * rad, 0.0);

			//Rotar accediendo mediante el nodo
			/*if (i % 2 == 0){
				Ogre::SceneNode* hora = mSM->getSceneNode("Hora " + std::to_string(i + 1));
				hora->setScale(0.5, 0.5, 0.5);
			}*/
		}
		// Agujas del reloj
		//agujasParent= Clock->createChildSceneNode("Agujas_Parent" );
		int i;
		for (i = 0; i < 2; i++) {
			Ogre::Entity* aguja = mSM->createEntity("cube.mesh");
			mAgujas[i] = Clock->createChildSceneNode("Aguja " + std::to_string(i + 1));
			mAgujas[i]->attachObject(aguja);
			mAgujas[i]->setScale(0.2 / (i + 1), 4, 0.1);

		}
		//creamos un nodo padre ficticio para rotar la aguja de los segundos
		segundosParent = Clock->createChildSceneNode("segundos_Parent");
		Ogre::Entity* secs = mSM->createEntity("cube.mesh");
		mAgujas[i] = segundosParent->createChildSceneNode("Aguja " + std::to_string(i + 1));
		mAgujas[i]->attachObject(secs);
		mAgujas[i]->setScale(0.2 / (i + 1), 4, 0.1);


		Ogre::SceneNode* agujaHora = mSM->getSceneNode("Aguja 1");
		agujaHora->translate(150, 0, 0);
		agujaHora->roll(Ogre::Degree(-90), Ogre::Node::TS_PARENT);
		Ogre::SceneNode* agujaMin = mSM->getSceneNode("Aguja 2");
		agujaMin->translate(0, 150, 0);
		Ogre::SceneNode* agujaSec = mSM->getSceneNode("Aguja 3");
		agujaSec->translate(-150, -80, 0);
		agujaSec->roll(Ogre::Degree(-240), Ogre::Node::TS_PARENT);
	}
	//apartados 14 y 15
	else if (scene == 14) {
		Ogre::Entity* sphere = mSM->createEntity("sphere.mesh");
		Sol = mSM->getRootSceneNode()->createChildSceneNode("Sol");
		Sol->attachObject(sphere);

		sphere = mSM->createEntity("sphere.mesh");
		Tierra = mSM->getRootSceneNode()->createChildSceneNode("Tierra");
		Tierra->attachObject(sphere);
		Tierra->translate(150,0,150);
		Tierra->scale(0.5, 0.5, 0.5);
		posIni=Tierra->getPosition();

		//nodo fictio padre de la Luna es hijo de la Tierra 
		sphere = mSM->createEntity("sphere.mesh");
		Ogre::SceneNode *lunaParent;
		lunaParent = Tierra->createChildSceneNode("LunaParent");
		Luna = lunaParent->createChildSceneNode("Luna");
		Luna->attachObject(sphere);
		Luna->translate(100, 0, 100);
		Luna->scale(0.1, 0.1, 0.1);

	}
	else if (scene == 16) {
		avion = new Avion(mSM->getRootSceneNode());
		addInputListener(avion);
	}

	else if (scene == 18) {
		MeshManager::getSingleton().createPlane("mPlane1080x800",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);		Ogre::Entity* plane = mSM->createEntity("mPlane1080x800");
		aspaNode = mSM->getRootSceneNode()->createChildSceneNode("aspa");

		aspaNode->attachObject(plane);
	}


	//------------------------------------------------------------------------

	mCamMgr = new OgreBites::CameraMan(mCamNode);
	addInputListener(mCamMgr);
	mCamMgr->setStyle(OgreBites::CS_ORBIT);

	//mCamMgr->setTarget(mSinbadNode);  
	//mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

	//------------------------------------------------------------------------

}
