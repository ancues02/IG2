#include "Simbad.h"

Simbad::Simbad(Ogre::SceneNode* parentNode):EntidadIG(parentNode)
{
	Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");
	simbadNode = mSM->getRootSceneNode()->createChildSceneNode("nSimbad");
	simbadNode->attachObject(ent);
	simbadNode->translate(-780, 100, 500);
	simbadNode->setScale(20, 20, 20);
}

Simbad::~Simbad()
{
}


