#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* parentNode):EntidadIG(parentNode)
{
	//mSM->createAnimationState("Sinbad.mesh");
	Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
	simbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSimbad");
	simbadNode->attachObject(ent);
	simbadNode->translate(-780, 100, 500);
	simbadNode->setScale(20, 20, 20);

	dance = true;

	animationState=ent->getAnimationState("Dance");
	animationState->setEnabled(dance);
	animationState->setLoop(true);
	
	
	as_runBot=ent->getAnimationState("RunBase");
	as_runBot->setEnabled(!dance);
	as_runBot->setLoop(true);

	as_runTop=ent->getAnimationState("RunTop");
	as_runTop->setEnabled(!dance);
	as_runTop->setLoop(true);
	//Ogre::Entity* sword = mSM->createEntity("Sword.mesh");
	//ent->attachObjectToBone("Handle.R", sword);
	//ent->detachObjectFromBone(sword);//para quitar la espada
}

Simbad::~Simbad()
{
}

void Simbad::receiveEvent(msg::MessageType msgType, EntidadIG* entidad)
{
	switch (msgType)
	{
	case msg::_CAMBIO_ANIM:
		dance = !dance;
		animationState->setEnabled(dance);
		as_runBot->setEnabled(!dance);
		as_runTop->setEnabled(!dance);
		break;
	default:
		break;
	}
}

void Simbad::frameRendered(const Ogre::FrameEvent& evt)
{
	if(dance)
		animationState->addTime(evt.timeSinceLastFrame);
	else{
		as_runBot->addTime(evt.timeSinceLastFrame);
		as_runTop->addTime(evt.timeSinceLastFrame);
	}
}


