#include "Avion.h"
Avion::Avion(Ogre::SceneNode* parentNode):EntidadIG(parentNode)
{
    // Apartado 16
    // Creacion de los nodos para cada elemento del avión
    avionNode = mNode->createChildSceneNode("avion");
    cuerpoNode = avionNode->createChildSceneNode("cuerpo_Node");
    alaINode = avionNode->createChildSceneNode("alaI_Node");
    alaDNode = avionNode->createChildSceneNode("alaD_Node");
    frenteNode = avionNode->createChildSceneNode("frente_Node");
    pilotoNode = avionNode->createChildSceneNode("piloto_Node");
    heliceNode_D = new AspasMolino(avionNode, 5);
    heliceNode_I = new AspasMolino(avionNode, 5);

    // Creacion del cuerpo del avion
    Ogre::Entity* ent = parentNode->getCreator()->createEntity("sphere.mesh");
	ent->setMaterialName("Practica1/rojeteEsf"); 
    cuerpoNode->attachObject(ent);

    // Creacion del ala izquierda
    ent = parentNode->getCreator()->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/tableroHelice");
	alaINode->attachObject(ent);
    alaINode->scale(4, 0.2, 1);
	alaINode->translate(100,0,0);
    
    // Creacion del ala derecha
	ent = parentNode->getCreator()->createEntity("cube.mesh");
	ent->setMaterialName("Practica1/tableroHelice");
	alaDNode->attachObject(ent);
    alaDNode->scale(4.0, 0.2, 1.0);
    alaDNode->translate(-100,0.0,0.0);

    // Creacion del piloto
    ent = parentNode->getCreator()->createEntity("ninja.mesh");
	ent->setMaterialName("Practica1/amarillete");
    pilotoNode->attachObject(ent);
	pilotoNode->yaw(Ogre::Degree(180.0));
	pilotoNode->scale(0.7, 0.7, 0.7);
    pilotoNode->translate(0.0, 20, 0.0);

    // Creaicion del frente del avion
    ent = parentNode->getCreator()->createEntity("Barrel.mesh");
	ent->setMaterialName("Practica1/naranjete");
    frenteNode->attachObject(ent);
    frenteNode->pitch(Ogre::Degree(90.0));
    frenteNode->scale(10, 3, 10);
	frenteNode->translate(0, 0, 100);

    auto aux = avionNode->getChild("aspas" + std::to_string(heliceNode_D->getID()));
    aux->translate(200,0,50, Ogre::Node::TS_LOCAL);//sin ficticio 
    aux->scale(0.2, 0.2, 0.2);
    aux = avionNode->getChild("aspas" + std::to_string(heliceNode_I->getID()));
	aux->translate(-200,0,50, Ogre::Node::TS_LOCAL);//sin ficticio 
	aux->scale(0.2, 0.2, 0.2);

   
	posIni = { 450, 500, 0 };
    
	//posIni = avionNode->getPosition();
	//auto aux2 = mSM->getSceneNode("avion");
    // Movemos al avion a su posicion
	avionNode->translate(posIni);
	//avionNode->yaw(Ogre::Degree(-50.0f));
	avionNode->scale(0.2, 0.2, 0.2);


    //Luz
    lightNode = avionNode->createChildSceneNode("luz_avion");

	Light* luzFoco = mSM->createLight("LuzFoco");
    //lightNode = mSM->createSceneNode();
	luzFoco->setType(Ogre::Light::LT_SPOTLIGHT);
	luzFoco->setDiffuseColour(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
	luzFoco->setDirection(Ogre::Vector3(1, -1, 0));
	/*luzFoco->setSpotlightInnerAngle(Ogre::Degree(1.0f));
	luzFoco->setSpotlightOuterAngle(Ogre::Degree(25.0f));*/
	luzFoco->setSpotlightFalloff(0.5f);

    lightNode->attachObject(luzFoco);
}

Avion::~Avion()
{
}

void Avion::receiveEvent(msg::MessageType msgType, EntidadIG* entidad)
{
}

void Avion::frameRendered(const Ogre::FrameEvent& evt){
    //movemos el avion con el truco
    avionNode->translate(-posIni, Ogre::Node::TS_LOCAL);      
    avionNode->yaw(Ogre::Degree(-1.0f), Node::TS_LOCAL);
    avionNode->translate(posIni, Ogre::Node::TS_LOCAL);

	//girar aspas de helice derecha
	auto aux = avionNode->getChild("aspas" + std::to_string(heliceNode_D->getID()));//sin ficticio
	Aspa** arrayAspas = heliceNode_D->getAspasArray();
	for (int i = 0; i < heliceNode_D->getNumAspas(); ++i) {
		aux->getChild("aspa_" + std::to_string(arrayAspas[i]->getAspaID()))->getChild("adorno_" + std::to_string(arrayAspas[i]->getAspaID()))->roll(Ogre::Degree(1.0f));

	}
	aux->roll(Ogre::Degree(-1.0f));

	//girar aspas de helice izquierda
	aux = avionNode->getChild("aspas" + std::to_string(heliceNode_I->getID()));//sin ficticio
	arrayAspas = heliceNode_I->getAspasArray();
	for (int i = 0; i < heliceNode_I->getNumAspas(); ++i) {
		aux->getChild("aspa_" + std::to_string(arrayAspas[i]->getAspaID()))->getChild("adorno_" + std::to_string(arrayAspas[i]->getAspaID()))->roll(Ogre::Degree(1.0f));

	}
	aux->roll(Ogre::Degree(-1.0f));

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