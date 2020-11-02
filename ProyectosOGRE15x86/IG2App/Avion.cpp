#include "Avion.h"
Avion::Avion(Ogre::SceneNode* parentNode):EntidadIG(parentNode)
{
    // Apartado 16
    // Creacion de los nodos para cada elemento del avión
    avionNode = mNode->createChildSceneNode("Avion");
    cuerpoNode = avionNode->createChildSceneNode("cuerpo_Node");
    alaINode = avionNode->createChildSceneNode("alaI_Node");
    alaDNode = avionNode->createChildSceneNode("alaD_Node");
    frenteNode = avionNode->createChildSceneNode("frente_Node");
    pilotoNode = avionNode->createChildSceneNode("piloto_Node");
    heliceNode_D = new AspasMolino(avionNode, 5);
    heliceNode_I = new AspasMolino(avionNode, 5);

    // Creacion del cuerpo del avion
    Ogre::Entity* ent = parentNode->getCreator()->createEntity("sphere.mesh");
    cuerpoNode->attachObject(ent);

    // Creacion del ala izquierda
    ent = parentNode->getCreator()->createEntity("cube.mesh");
	alaINode->attachObject(ent);
    alaINode->scale(4, 0.2, 1);
	alaINode->translate(100,0,0);
    
    // Creacion del ala derecha
	ent = parentNode->getCreator()->createEntity("cube.mesh");
	alaDNode->attachObject(ent);
    alaDNode->scale(4.0, 0.2, 1.0);
    alaDNode->translate(-100,0.0,0.0);

    // Creacion del piloto
    ent = parentNode->getCreator()->createEntity("ninja.mesh");
    pilotoNode->attachObject(ent);
	pilotoNode->yaw(Ogre::Degree(180.0));
	pilotoNode->scale(0.7, 0.7, 0.7);
    pilotoNode->translate(0.0, 20, 0.0);

    // Creaicion del frente del avion
    ent = parentNode->getCreator()->createEntity("Barrel.mesh");
    frenteNode->attachObject(ent);
    frenteNode->pitch(Ogre::Degree(90.0));
    frenteNode->scale(10, 3, 10);
	frenteNode->translate(0, 0, 100);

    auto aux = avionNode->getChild("aspas1");
    aux->translate(200,0,50, Ogre::Node::TS_LOCAL);//sin ficticio 
    aux->scale(0.2, 0.2, 0.2);
    aux = avionNode->getChild("aspas2");
	aux->translate(-200,0,50, Ogre::Node::TS_LOCAL);//sin ficticio 
	aux->scale(0.2, 0.2, 0.2);


}

Avion::~Avion()
{
}

void Avion::receiveEvent(msg::MessageType msgType, EntidadIG* entidad)
{
}

// Apartado 17
/*bool Avion::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_g) 
    {
        auto aux = avionNode->getChild("aspas1");
		aux->roll(Ogre::Degree(-10.0));
		aux = avionNode->getChild("aspas2");
		aux->roll(Ogre::Degree(-10.0));
    }
    
    return true;
}*/