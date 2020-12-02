#include "Plano.h"


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
	delete mpRef; mpRef = nullptr;
}

bool Plano::keyPressed(const OgreBites::KeyboardEvent& evt)
{
	switch (evt.keysym.sym) {
	
	case SDLK_r://rotan aspas
		sendEvent(msg::_PARAR, this);
		break;
	default:
		break;
	}
	return false;
}
void Plano::setReflejo(Camera* cam)
{	

	mpRef= new MovablePlane(Vector3::UNIT_Y, 0);
	planoNode->attachObject(mpRef);

	Camera* camRef = mSM->createCamera("RefCam");
	mSM->getSceneNode("nCam")->attachObject(camRef);

	camRef->setNearClipDistance(cam->getNearClipDistance());
	camRef->setFarClipDistance(cam->getFarClipDistance());
	camRef->setAutoAspectRatio(true);

	camRef->enableReflection(mpRef);
	camRef->enableCustomNearClipPlane(mpRef);

	TexturePtr rttRef = TextureManager::getSingleton().createManual(
		"rttReflejo", 
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		1080,800,
		0, PF_R8G8B8, TU_RENDERTARGET);


	RenderTexture* renderTexture= rttRef->getBuffer()->getRenderTarget();
	Viewport * vpt = renderTexture->addViewport(camRef); // ocupando toda
	vpt->setClearEveryFrame(true); 
	vpt->setBackgroundColour(ColourValue::White); 

	TextureUnitState* tu = plane->getSubEntity(0)->getMaterial()->getTechnique(0)->
	getPass(0)->createTextureUnitState("rttReflejo"); 
	tu->setColourOperation(LBO_MODULATE);
	tu->setProjectiveTexturing(true, camRef);

	renderTexture->addListener(this);
}

void Plano::preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	SceneNode* cara=mSM->getSceneNode("cara");
	static_cast<Entity*>(cara->getAttachedObjects()[0])->setMaterialName("Practica1/caraRotada");
}

void Plano::postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt)
{
	SceneNode* cara = mSM->getSceneNode("cara");
	static_cast<Entity*>(cara->getAttachedObjects()[0])->setMaterialName("Practica1/cara");

}


void Plano::receiveEvent(msg::MessageType msgType, EntidadIG* entidad)
{
	if (entidad == this) {
		switch (msgType) {
		case msg::_PARAR:
			plane->setMaterialName("Practica1/rioSeco");
			break;
		default:
			break;
		}
	}
}

void Plano::setMaterial(std::string name)
{
	plane->setMaterialName(name);

}
