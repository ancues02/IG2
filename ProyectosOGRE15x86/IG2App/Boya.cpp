#include "Boya.h"

Boya::Boya(Ogre::SceneNode* parentNode) : EntidadIG(parentNode)
{
	bCilindro = mNode->createChildSceneNode();

	bEnt = mSM->createEntity("Barrel.mesh");
	bEnt->setMaterialName("Practica1/tableroHelice");
	bCilindro->attachObject(bEnt);
	Vector3 _scale = { 30, 40, 30 };
	bCilindro->scale(_scale);

	bCilindro->setInitialState();
	int duracion=16;
	//---------------------
	Animation * animation = mSM -> createAnimation("animVV", duracion);
	animation->setInterpolationMode(Ogre::Animation::IM_SPLINE);
	animation->setRotationInterpolationMode(Ogre::Animation::RIM_SPHERICAL);
	NodeAnimationTrack * track = animation -> createNodeTrack(0);
	track -> setAssociatedNode(bCilindro);
	Vector3 keyframePos(0.0, 0.0, 0.0);  Vector3 src(0, 0, 1);
	Real durPaso = duracion / 4.0; // uniformes
	TransformKeyFrame * kf; // 5 keyFrames: origen(0), arriba, origen, abajo, origen(4)
	kf = track->createNodeKeyFrame(durPaso * 0); // Keyframe 0: origen
	kf->setTranslate(keyframePos); // Origen: Vector3
	kf->setRotation(src.getRotationTo(src));

	kf = track -> createNodeKeyFrame(durPaso * 1); // Keyframe 1: arriba
	keyframePos += Ogre::Vector3::UNIT_Y * long_desp;
	kf->setTranslate(keyframePos); // Origen: Vector3
	kf->setRotation(src.getRotationTo(Vector3(1, 0, 1))); // Yaw(-45)

	kf = track -> createNodeKeyFrame(durPaso * 2); // Keyframe 0: origen
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * long_desp;
	kf->setTranslate(keyframePos); // Origen: Vector3

	kf = track -> createNodeKeyFrame(durPaso * 3); // Keyframe 0: abajo
	keyframePos += Ogre::Vector3::NEGATIVE_UNIT_Y * long_desp;
	kf->setTranslate(keyframePos); // Origen: Vector3
	kf->setRotation(src.getRotationTo(Vector3(-1, 0, 1))); // Yaw(-45)

	kf = track -> createNodeKeyFrame(durPaso * 4); // Keyframe 0: origen
	keyframePos += Ogre::Vector3::UNIT_Y * long_desp;
	kf->setTranslate(keyframePos); // Origen: Vector3

	animationState = mSM->createAnimationState("animVV");
	animationState -> setLoop(true);
	animationState -> setEnabled(true);

}

void Boya::frameRendered(const Ogre::FrameEvent& evt)
{
	animationState->addTime(evt.timeSinceLastFrame);
}

Boya::~Boya()
{
}
