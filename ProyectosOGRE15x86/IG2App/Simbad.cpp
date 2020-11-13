#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* parentNode):EntidadIG(parentNode)
{
	//mSM->createAnimationState("Sinbad.mesh");
	simbadEnt = mSM->createEntity("Sinbad.mesh");
	simbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSimbad");
	simbadNode->attachObject(simbadEnt);
	simbadNode->translate(-780, 100, 500);
	simbadNode->setScale(20, 20, 20);

	//dance = true;

	animationState=simbadEnt->getAnimationState("Dance");
	animationState->setEnabled(dance);
	animationState->setLoop(true);
	
	
	as_runBot=simbadEnt->getAnimationState("RunBase");
	as_runBot->setEnabled(!dance);
	as_runBot->setLoop(true);

	as_runTop=simbadEnt->getAnimationState("RunTop");
	as_runTop->setEnabled(!dance);
	as_runTop->setLoop(true);

	sword = mSM->createEntity("Sword.mesh");
	simbadEnt->attachObjectToBone("Handle.R", sword);
	//simbadEnt->detachObjectFromBone(sword);//para quitar la espada
	dcha = true;
}

Simbad::~Simbad()
{
}

bool Simbad::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym) {
	case SDLK_c://cambiar animacion
		sendEvent(msg::_CAMBIO_ANIM, this);
		break;
	case SDLK_e://cambiar animacion
		sendEvent(msg::_CAMBIO_ESPADA, this);
		break;
	default:
		break;
	}
	return false;
};

void Simbad::receiveEvent(msg::MessageType msgType, EntidadIG* entidad)
{	
	if (entidad == this) {
		switch (msgType)
		{
		case msg::_CAMBIO_ANIM:
			dance = !dance;
			animationState->setEnabled(dance);
			as_runBot->setEnabled(!dance);
			as_runTop->setEnabled(!dance);
			break;
		case msg::_CAMBIO_ESPADA:
			dcha = !dcha;
			if (dcha) {
				simbadEnt->detachObjectFromBone(sword);//para quitar la espada
				simbadEnt->attachObjectToBone("Handle.R", sword);
			}
			else {
				simbadEnt->detachObjectFromBone(sword);//para quitar la espada
				simbadEnt->attachObjectToBone("Handle.L", sword);
			}
			break;
		default:
			break;
		}
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


