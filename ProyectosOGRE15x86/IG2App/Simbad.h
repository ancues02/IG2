#pragma once
#include "Aspa.h"
using namespace Ogre;

class Simbad : public EntidadIG
{
public:
	Simbad(Ogre::SceneNode* parentNode);
	~Simbad();
	
private:
	Ogre::SceneNode* simbadNode = nullptr;
};
