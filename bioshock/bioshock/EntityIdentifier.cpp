#include "EntityIdentifier.h"

unsigned int EntityIdentifier::m_mainCamera = 0;
unsigned int EntityIdentifier::m_mainPlayer = 0;
unsigned int EntityIdentifier::m_crosshair = 0;
unsigned int EntityIdentifier::m_guntrail = 0;
unsigned int EntityIdentifier::m_healthpack = 0;
unsigned int EntityIdentifier::m_ammocount10s = 0; 
unsigned int EntityIdentifier::m_ammocount1s = 0; 
unsigned int EntityIdentifier::m_healthbar = 0;
unsigned int EntityIdentifier::m_manabar = 0;
unsigned int EntityIdentifier::m_lightning = 0;

//start on 0x1
unsigned int EntityIdentifier::m_cameraBit			= 0x1;
unsigned int EntityIdentifier::m_spriteBit			= 0x10;
unsigned int EntityIdentifier::m_transformBit		= 0x100;
unsigned int EntityIdentifier::m_animationBit		= 0x1000;
unsigned int EntityIdentifier::m_linkBit			= 0x10000;
unsigned int EntityIdentifier::m_physicsBit			= 0x100000;
unsigned int EntityIdentifier::m_horiScrollCameraBit= 0x1000000;
unsigned int EntityIdentifier::m_vertScrollCameraBit= 0x10000000;
//start on 0x2
unsigned int EntityIdentifier::m_hudAspectBit		= 0x2;
unsigned int EntityIdentifier::m_enResourcesBit		= 0x20;

//(having just camera means the bit = 1)
//(having sprite, animation and transform)
//0x0111

void EntityIdentifier::AddComponent(unsigned int component)
{
	//Adds the component to the identifier
	m_identifier |= component;
}

unsigned int EntityIdentifier::MainPlayer()
{
	//Gets the main player entity number
	return m_mainPlayer;
}

bool EntityIdentifier::GetIsMainPlayer() const
{
	//Gets if this component IS attached to the main player
	return m_isMainPlayer;
}

unsigned int EntityIdentifier::MainCamera()
{
	//Gets the main camera entity number
	//*There will ALWAYS be a camera, and if there isn't
	//*nothing will draw
	return m_mainCamera;
}

bool EntityIdentifier::GetIsMainCamera() const
{
	//Gets if this component IS attached to the main camera
	return m_isMainCamera;
}

unsigned int EntityIdentifier::Crosshair()
{
	return m_crosshair;
}

bool EntityIdentifier::GetIsCrosshair() const
{
	return m_isCrosshair;
}

unsigned int EntityIdentifier::GunTrail()
{
	return m_guntrail;
}

bool EntityIdentifier::GetIsGunTrail() const
{
	return m_isGuntrail;
}

unsigned int EntityIdentifier::HealthPack()
{
	return m_healthpack;
}

bool EntityIdentifier::GetIsHealthPack()
{
	return m_isHealthpack;
}

unsigned int EntityIdentifier::AmmoCount10s()
{
	return m_ammocount10s;
}

bool EntityIdentifier::GetIsAmmoCount10s()
{
	return m_isAmmocount10s;
}

unsigned int EntityIdentifier::AmmoCount1s()
{
	return m_ammocount1s;
}

bool EntityIdentifier::GetIsAmmoCount1s()
{
	return m_isAmmocount1s;
}

unsigned int EntityIdentifier::HealthBar()
{
	return m_healthbar;
}

bool EntityIdentifier::GetIsHealthBar()
{
	return m_isHealthbar;
}

unsigned int EntityIdentifier::ManaBar()
{
	return m_manabar;
}

bool EntityIdentifier::GetIsManaBar()
{
	return m_isManabar;
}

unsigned int EntityIdentifier::Lightning()
{
	return m_lightning;
}

bool EntityIdentifier::GetIsLightning()
{
	return m_isLightning;
}

unsigned int EntityIdentifier::GetEntity() const
{
	//Gets the entity number
	return m_entity;
}

unsigned int EntityIdentifier::GetIdentifier() const
{
	//Gets the identifier that holds all components
	return m_identifier;
}

std::string EntityIdentifier::GetName() const
{
	//Get the name of the entity
	return m_name;
}

bool& EntityIdentifier::GetSelected()
{
	//Gets if this is selected
	return m_selected;
}

unsigned int EntityIdentifier::CameraBit()
{
	//Gets the bit for the Camera
	return m_cameraBit;
}

unsigned int EntityIdentifier::SpriteBit()
{
	//Gets the bit for the Sprite
	return m_spriteBit;
}

unsigned int EntityIdentifier::TransformBit()
{
	//Gets the bit for the Transform
	return m_transformBit;
}

unsigned int EntityIdentifier::AnimationBit()
{
	//Gets the bit for the Animation Controller
	return m_animationBit;
}

unsigned int EntityIdentifier::LinkBit()
{
	//Gets the bit for Link
	return m_linkBit;
}

unsigned int EntityIdentifier::PhysicsBit()
{
	//Gets the bit for the Physics Body
	return m_physicsBit;
}

unsigned int EntityIdentifier::HoriScrollCameraBit()
{
	return m_horiScrollCameraBit;
}

unsigned int EntityIdentifier::VertScrollCameraBit()
{
	return m_vertScrollCameraBit;
}

unsigned int EntityIdentifier::HudAspectBit()
{
	return m_hudAspectBit;
}

unsigned int EntityIdentifier::EnResourcesBit()
{
	return m_enResourcesBit;
}

void EntityIdentifier::MainPlayer(unsigned int entity)
{
	//Sets the main player entity
	m_mainPlayer = entity;
}

void EntityIdentifier::SetIsMainPlayer(bool main)
{
	//Sets whether or not the entity that has this component, is the main player
	m_isMainPlayer = main;
}

void EntityIdentifier::MainCamera(unsigned int entity)
{
	//Sets the main camera entity
	m_mainCamera = entity;
}

void EntityIdentifier::SetIsMainCamera(bool main)
{
	//Sets whether or not the entity that has this component, is the main camera
	m_isMainCamera = main;
}

void EntityIdentifier::Crosshair(unsigned int entity)
{
	m_crosshair = entity; 
}

void EntityIdentifier::SetIsCrosshair(bool main)
{
	m_isCrosshair = true;
}

void EntityIdentifier::GunTrail(unsigned int entity)
{
	m_guntrail = entity; 
}

void EntityIdentifier::SetIsGunTrail(bool main)
{
	m_isGuntrail = main; 
}

void EntityIdentifier::HealthPack(unsigned int entity)
{
	m_healthpack = entity;
}

void EntityIdentifier::SetIsHealthPack(bool main)
{
	m_isHealthpack = main;
}

void EntityIdentifier::AmmoCount10s(unsigned int entity)
{
	m_ammocount10s = entity;
}

void EntityIdentifier::SetIsAmmoCounts10s(bool main)
{
	m_isAmmocount10s = main;
}

void EntityIdentifier::AmmoCount1s(unsigned int entity)
{
	m_ammocount1s = entity; 
}

void EntityIdentifier::SetIsAmmoCount1s(bool main)
{
	m_isAmmocount1s = main; 
}

void EntityIdentifier::Healthbar(unsigned int entity)
{
	m_healthbar = entity;
}

void EntityIdentifier::SetIsHealthbar(bool main)
{
	m_isHealthbar = main;
}

void EntityIdentifier::Manabar(unsigned int entity)
{
	m_manabar = entity; 
}

void EntityIdentifier::SetIsManabar(bool main)
{
	m_isManabar = main;
}

void EntityIdentifier::Lightning(unsigned int entity)
{
	m_lightning = entity; 
}

void EntityIdentifier::SetIsLightning(bool main)
{
	m_isLightning = main;
}

void EntityIdentifier::SetIsEntity(bool main)
{
	m_isCrosshair = true;
}

void EntityIdentifier::SetEntity(unsigned int entity)
{
	//Sets the entity number
	m_entity = entity;
}

void EntityIdentifier::SetIdentifier(unsigned int identity)
{
	//Sets the identifier
	m_identifier = identity;
}

void EntityIdentifier::SetName(std::string name)
{
	//Set the name of the entity
	m_name = name;
}

void EntityIdentifier::SetSelected(bool selected)
{
	//Set whether the entity is selected
	m_selected = selected;
}
