#include "EntidadIG.h"

// Inicialización del vector de listeners
std::vector<EntidadIG*> EntidadIG::appListeners =
std::vector<EntidadIG*>(0, nullptr);

EntidadIG::EntidadIG(SceneNode* node)
{	
	mNode = node;
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
	return false;
};