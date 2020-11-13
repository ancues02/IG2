#include "EntidadIG.h"

// Inicialización del vector de listeners
std::vector<EntidadIG*> EntidadIG::appListeners =
std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(SceneNode* node)
{	
	mNode = node;
	//node->createChildSceneNode("");
	//mSM->createChildSceneNoce("");
	mSM = mNode->getCreator();
}

void EntidadIG::addListener(EntidadIG* entidad)
{
	appListeners.push_back(entidad);
}

void EntidadIG::sendEvent(msg::MessageType msgType, EntidadIG* entidad)
{
	for (EntidadIG* e : appListeners)
		e->receiveEvent(msgType, this);
}

bool EntidadIG::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	//switch (evt.keysym.sym) {
	//case SDLK_g://rotan aspas
	//	sendEvent(msg::_GIRAR_ASPAS, this);
	//	break;
	//case SDLK_c://el cilindro central de las aspas se mueve hacia dentro
	//	sendEvent(msg::_ACERCAR_CENTRO_ASPAS, this);
	//	sendEvent(msg::_CAMBIO_ANIM, this);
	//	break;
	//case SDLK_h://las aspas giran al rededor del molino
	//	sendEvent(msg::_ALREDEDOR_MOLINO, this);
	//	break;
	//case SDLK_r://paran un monton de animaciones
	//	sendEvent(msg::_PARAR, this);
	//	break;
	//
	///*case SDLK_j://gira la tierra al rederor del sol
	//	sendEvent(msg::_GIRAR_ASPAS, this);
	//	break;*/
	//default:
	//	return false;
	//	break;
	//}	
	return false;
};