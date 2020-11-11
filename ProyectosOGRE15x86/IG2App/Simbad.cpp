#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* parentNode):EntidadIG(parentNode)
{
	//mSM->createAnimationState("Sinbad.mesh");
	Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
	simbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSimbad");
	simbadNode->attachObject(ent);
	simbadNode->translate(-780, 100, 500);
	simbadNode->setScale(20, 20, 20);

	animationState=ent->getAnimationState("Dance");
	animationState->setEnabled(true);
	animationState->setLoop(true);
	
	//Ogre::Entity* sword = mSM->createEntity("Sword.mesh");
	//ent->attachObjectToBone("Handle.R", sword);
	//ent->detachObjectFromBone(sword);//para quitar la espada
}

Simbad::~Simbad()
{
}

void Simbad::receiveEvent(msg::MessageType msgType, EntidadIG* entidad)
{
}

void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	
	animationState->addTime(evt.timeSinceLastFrame);
}


