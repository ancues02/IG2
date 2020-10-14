#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* parentNode)
{
	aspaNode = parentNode->createChildSceneNode("aspa_");
	tableroNode = aspaNode->createChildSceneNode("tablero_");
	cilindroNode = aspaNode->createChildSceneNode("adorno_");

    Ogre::Entity* ent = parentNode->getCreator()->createEntity("cube.mesh");
    tableroNode->attachObject(ent);
    tableroNode->setScale(5, 1, 0.1);


    /*Ogre::SceneNode* adorno = numAspas[i]->createChildSceneNode("adorno_" + std::to_string(i + 1));
    ent = mSM->createEntity("Barrel.mesh");
    adorno->attachObject(ent);
    adorno->setScale(5, 10, 5);
    adorno->setPosition(150, 0, 20);*/
}

Aspa::~Aspa()
{
}
