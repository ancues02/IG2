#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* parentNode):EntidadIG(parentNode)
{
	//mSM->createAnimationState("Sinbad.mesh");
	simbadEnt = mSM->createEntity("Sinbad.mesh");
	simbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSimbad");
	simbadNode->attachObject(simbadEnt);

	keyframePos = Vector3(780, 0, -500);
	simbadNode->setScale(20, 20, 20);
	simbadNode->translate(-780, 100, 500);

	simbadNode->setInitialState();
	// Skeletal animation
	dance = true;
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
	dcha = true;
	//------------------------------------------------------------------------------------

	// ScenNode animation
	int duracion = 16;
	Animation* animation = mSM->createAnimation("animSB", duracion);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	animation->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);
	NodeAnimationTrack* track = animation->createNodeTrack(0);
	track->setAssociatedNode(simbadNode);
	Vector3 keyframeOrigen = Vector3(0, 0, 0);
	Vector3 src(0, 0, 1);
	Real durPasoMover = duracion / 4.0; // uniformes
	TransformKeyFrame* kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
	kf = track->createNodeKeyFrame(durPasoMover * 0); // Keyframe 0: posicion inicial
	kf->setTranslate(keyframeOrigen); // Origen
	kf->setRotation(src.getRotationTo(Vector3(1, 0, -1)));//rotamos para que mire al destino

	kf = track->createNodeKeyFrame(durPasoMover * 1); // Keyframe 1: posicion final
	kf->setTranslate(keyframePos); // Posicion final
	kf->setRotation(src.getRotationTo(Vector3(1, 0, -1)));//dejamos la misma rotacion

	kf = track->createNodeKeyFrame(durPasoMover * 2); // Keyframe 2: posicion final rotado
	kf->setTranslate(keyframePos); // Se mantiene en la posicion final
	kf->setRotation(src.getRotationTo(Vector3(-0.7, 0, 0.7))); //rotamos para que mire a su posicion inicial

	kf = track->createNodeKeyFrame(durPasoMover * 3); // Keyframe 3: posicion inicial
	kf->setTranslate(keyframeOrigen); // Vuelve al origen
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1)));// dejamos la misma rotacion

	kf = track->createNodeKeyFrame(durPasoMover * 4); // Keyframe 4: posicion inicial rotado
	kf->setTranslate(keyframeOrigen); // Se mantiene en la posicion origen
	kf->setRotation(src.getRotationTo(Vector3(0.7, 0, -0.7))); //rotamos para que mire al destino

	run_animation = mSM->createAnimationState("animSB");
	run_animation->setLoop(true);
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
			run_animation->setEnabled(!dance);
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
	// Skeletal animation
	if(dance)
		animationState->addTime(evt.timeSinceLastFrame);
	else{
		as_runBot->addTime(evt.timeSinceLastFrame);
		as_runTop->addTime(evt.timeSinceLastFrame);
		run_animation->addTime(evt.timeSinceLastFrame); // Node animation
	}
}