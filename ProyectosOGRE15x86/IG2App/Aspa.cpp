#include "Aspa.h"

Aspa::Aspa(Ogre::SceneNode* parentNode)
{
	aspaNode = parentNode->createChildSceneNode("aspa_" + std::to_string(cont + 1));
	tableroNode = aspaNode->createChildSceneNode("tablero_" + std::to_string(cont + 1));
	cilindroNode = aspaNode->createChildSceneNode("adorno_" + std::to_string(cont + 1));

    Ogre::Entity* ent = parentNode->getCreator()->createEntity("cube.mesh");
    tableroNode->attachObject(ent);
    tableroNode->setScale(5, 1, 0.1);


    ent = parentNode->getCreator()->createEntity("Barrel.mesh");
    cilindroNode->attachObject(ent);
    cilindroNode->setScale(5, 10, 5);
    cilindroNode->setPosition(150, 0, 20);

    cont++;
}
int Aspa::cont = 0;

Aspa::~Aspa()
{
}

bool Aspa::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    return false;
}

AspasMolino::AspasMolino(Ogre::SceneNode* parentNode, int nAspas) : numAspas(nAspas)
{
    aspasNode = parentNode->createChildSceneNode("aspas");//creamos el nodo de las aspas como hijo del que nos pasan
    centroNode = aspasNode->createChildSceneNode("centro_aspas");
    Ogre::Entity* ent = parentNode->getCreator()->createEntity("Barrel.mesh");
	centroNode->attachObject(ent);
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
        Node* aux = aspasNode->getChild("aspa_" + std::to_string(i + 1));
        aux->roll(Ogre::Degree(rotation), Ogre::Node::TS_PARENT);
        aux->translate(200, 0, 0, Ogre::Node::TS_LOCAL);
        aux->getChild("adorno_" + std::to_string(i + 1))->roll(Ogre::Degree(-rotation));

    }
}

AspasMolino::~AspasMolino()
{
}

// Apartados 6 y 8
bool AspasMolino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    if (evt.keysym.sym == SDLK_g) // #include <SDL_keycode.h>
    {
        for (int i = 0; i < numAspas; i++) {
            aspasNode->getChild("aspa_" + std::to_string(i + 1))->getChild("adorno_" + std::to_string(i + 1))->roll(Ogre::Degree(10.0f));
        }
        aspasNode->roll(Ogre::Degree(-10.0f));
    }
    return true;
}

Molino::Molino(Ogre::SceneNode* parentNode, int nAspas)
{

    esfera = parentNode->createChildSceneNode("esfera");//creamos el nodo de las aspas como hijo del que nos pasan
    Ogre::Entity* ent = parentNode->getCreator()->createEntity("Barrel.mesh");
    ent = parentNode->getCreator()->createEntity("sphere.mesh");

}

Molino::~Molino()
{
}

bool Molino::keyPressed(const OgreBites::KeyboardEvent& evt)
{
    return false;
}
