#include "Aspa.h"
#include <iostream>
Aspa::Aspa(Ogre::SceneNode* parentNode) : EntidadIG(parentNode)
{
    
	aspaNode = mNode->createChildSceneNode("aspa_" + std::to_string(cont + 1));
	tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(cont + 1));
	cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(cont + 1));

    Ogre::Entity* ent = mSM->createEntity("cube.mesh");
    tableroNode->attachObject(ent);
    tableroNode->setScale(5, 1, 0.1);


    ent = mSM->createEntity("Barrel.mesh");
    cilindroNode->attachObject(ent);
    cilindroNode->setScale(5, 10, 5);
    cilindroNode->setPosition(150, 0, 20);
    cont++;
	id = cont;

}

int Aspa::cont = 0;

Aspa::~Aspa()
{
}

AspasMolino::AspasMolino(Ogre::SceneNode* parentNode, int nAspas) : EntidadIG(parentNode), numAspas(nAspas)
{
    aspasNode = mNode->createChildSceneNode("aspas" + std::to_string(cont + 1));//creamos el nodo de las aspas como hijo del que nos pasan
    centroNode = aspasNode->createChildSceneNode("centro_aspas" + std::to_string(cont + 1));
    Ogre::Entity* ent = mSM->createEntity("Barrel.mesh");
	centroNode->attachObject(ent);
    centroNode->pitch(Ogre::Degree(90.0));
    centroNode->setScale(20, 5, 20);
    arrayAspas = new Aspa*[numAspas];//array de tamaño del numero de aspas
    for (int i = 0; i < numAspas; i++) {
		// Apartado 5
		//creamos las aspas a sin utilizar la clase Aspa
		/*SceneNode* aspa = aspasNode->createChildSceneNode("aspa_" + std::to_string(i + 1));
		SceneNode* tablero = aspa->createChildSceneNode("tablero_" + std::to_string(i + 1));
		Ogre::Entity* ent = parentNode->getCreator()->createEntity("cube.mesh");
		tablero->attachObject(ent);
		tablero->setScale(5, 1, 0.1);
		Ogre::SceneNode* adorno = aspa->createChildSceneNode("adorno_" + std::to_string(i + 1));
		ent = parentNode->getCreator()->createEntity("Barrel.mesh");
		adorno->attachObject(ent);
		adorno->setScale(5, 10, 5);
		adorno->setPosition(150, 0, 20);
		float rotation = (360.0f / numAspas) * i;
		aspa->roll(Ogre::Degree(rotation), Ogre::Node::TS_PARENT);
		aspa->translate(200, 0, 0, Ogre::Node::TS_LOCAL);
		adorno->roll(Ogre::Degree(-rotation));*/

        // Apartado 7
        arrayAspas[i] = new Aspa(aspasNode);
        float rotation = (360.0f / numAspas) * i;
        Node* aux = aspasNode->getChild("aspa_" + std::to_string(arrayAspas[i]->getAspaID()));
        aux->roll(Ogre::Degree(rotation), Ogre::Node::TS_PARENT);
        aux->translate(200, 0, 0, Ogre::Node::TS_LOCAL);
        aux->getChild("adorno_" + std::to_string(arrayAspas[i]->getAspaID()))->roll(Ogre::Degree(-rotation));
    }
    addListener(this);
    cont++; id = cont;
}

int AspasMolino::cont = 0;

AspasMolino::~AspasMolino()
{
}

void AspasMolino::receiveEvent(msg::MessageType msgType, EntidadIG* entidad)
{
    
    switch (msgType)
    {
    case msg::_GIRAR_ASPAS:
    {
        for (int i = 0; i < numAspas; i++) {
           aspasNode->getChild("aspa_"+ std::to_string(arrayAspas[i]->getAspaID()))->getChild("adorno_"+ std::to_string(arrayAspas[i]->getAspaID()))->roll(Ogre::Degree(10.0f));
        }
        aspasNode->roll(Ogre::Degree(-10.0f));
    }
        break;
    case msg::_ACERCAR_CENTRO_ASPAS:
        centroNode->translate(0, 0, -2);
        break;
    default:
        break;
    }
}

// Apartados 6 y 8
//bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
//{
//    if (evt.keysym.sym == SDLK_g) // #include <SDL_keycode.h>
//    {
//        for (int i = 0; i < numAspas; i++) {
//            aspasNode->getChild("aspa_" + std::to_string(i + 1))->getChild("adorno_" + std::to_string(i + 1))->roll(Ogre::Degree(10.0f));
//        }
//        aspasNode->roll(Ogre::Degree(-10.0f));
//    }
//    //apartado 10
//    else if (evt.keysym.sym == SDLK_c) 
//    {
//        aspasNode->getChild("centro_aspas")->translate(0,0,-2);
//        
//    }
//    return true;
//}

Molino::Molino(Ogre::SceneNode* parentNode, int nAspas): EntidadIG(parentNode),  numAspas(nAspas)
{
    molinoNode= mNode->createChildSceneNode("molino");
    esfera = molinoNode->createChildSceneNode("esfera_techo");
    cilCuerpo = molinoNode->createChildSceneNode("cil_cuerpo");

    aspasMolino = new AspasMolino(molinoNode, numAspas);//sin ficticio
    molinoNode->getChild("aspas" + std::to_string(aspasMolino->getID()))->setScale(0.5, 0.5, 0.5);//sin ficticio
    molinoNode->getChild("aspas"+ std::to_string(aspasMolino->getID()))->translate(0, 0, 130);//sin ficticio


    /*ficticio = mNode->createChildSceneNode("ficticio");//con ficticio
    aspasMolino = new AspasMolino(ficticio, numAspas);//con ficticio
    ficticio->getChild("aspas1")->setScale(0.5, 0.5, 0.5);//con ficticio
    ficticio->getChild("aspas1")->translate(0, 0, 130);//con ficticio
    */

    Ogre::Entity* ent = mSM->createEntity("sphere.mesh");    
    esfera->attachObject(ent);
    esfera->setScale(1.2, 1.2, 1.2);

    ent = mSM->createEntity("Barrel.mesh");
  	cilCuerpo->attachObject(ent);
    cilCuerpo->setScale(50, 50, 50);
    cilCuerpo->translate(0, -150, 0);
    posIni = molinoNode->getChild("aspas" + std::to_string(aspasMolino->getID()))->getPosition();

    addListener(this);
}

Molino::~Molino()
{
}

void Molino::receiveEvent(msg::MessageType msgType, EntidadIG* entidad)
{
    switch (msgType)
    {
    case msg::_ALREDEDOR_MOLINO:
    {
        //Vector3 aux=mNode->getChild("aspas1")->getPosition();//no funciona porque pilla la posicion con respecto al padre

        molinoNode->getChild("aspas1")->translate(-posIni, Ogre::Node::TS_LOCAL);//sin ficticio        
        molinoNode->getChild("aspas1")->yaw(Ogre::Degree(-10.0f), Node::TS_PARENT);//sin ficticio
        molinoNode->getChild("aspas1")->translate(posIni, Ogre::Node::TS_LOCAL);//sin ficticio


        //mNode->getChild("ficticio")->yaw(Ogre::Degree(-10.0f));//con ficticio
    }
    break;
    default:
        break;
    }
}