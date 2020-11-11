#include "Plano.h"
#include <OgreMeshManager.h>

Plano::Plano(Ogre::SceneNode* parentNode):EntidadIG(parentNode) {
	MeshManager::getSingleton().createPlane("mPlane1080x800" + std::to_string(cont + 1),
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0),
		1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);
	plane = mSM->createEntity("mPlane1080x800" + std::to_string(cont + 1));
	planoNode = mNode->createChildSceneNode("plano_" + std::to_string(cont + 1));
	planoNode->attachObject(plane);
	cont++; id = cont;

}

int Plano::cont = 0;

Plano::~Plano() {
	//delete plane;
}

void Plano::receiveEvent(msg::MessageType msgType, EntidadIG* entidad)
{
	switch(msgType) {
	case msg::_PARAR:
		plane->setMaterialName("Practica1/rioSeco");
		break;
		default:
			break;
	}
}

void Plano::setMaterial(std::string name)
{
	plane->setMaterialName(name);

}
