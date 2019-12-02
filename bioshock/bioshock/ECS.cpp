#include "ECS.h"

entt::registry* ECS::m_reg = nullptr;

void ECS::AttachRegister(entt::registry * reg)
{
	//Attach reference to the registry
	m_reg = reg;
}

void ECS::UnattachRegister()
{
	//Unattaches the register
	m_reg = nullptr;
}

unsigned ECS::CreateEntity()
{
	//create the entity
	auto entity = m_reg->create();

	//Attach Entity Identifier to the entity
	m_reg->assign<EntityIdentifier>(entity);

	//Return entity ID
	return entity;
}

void ECS::DestroyEntity(unsigned entity)
{
	//Destroys the entity
	m_reg->destroy(entity);
}

void ECS::SetUpIdentifier(unsigned entity, unsigned componentID, std::string name)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Set the entity
	id.SetEntity(entity);
	//Set the entity identifier unsigned int
	id.AddComponent(componentID);
	//Set the name of the entity
	id.SetName(name);
}

void ECS::SetIsMainCamera(unsigned entity, bool mainCamera)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets main camera entity
	EntityIdentifier::MainCamera(entity);
	//Sets whether this entity is the main camera
	id.SetIsMainCamera(mainCamera);
}

void ECS::SetIsMainPlayer(unsigned entity, bool mainPlayer)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets main player entity
	EntityIdentifier::MainPlayer(entity);
	//Sets whether this entity is the main player
	id.SetIsMainPlayer(mainPlayer);
}

void ECS::SetIsCrosshair(unsigned entity, bool crosshair)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets crosshair entity
	EntityIdentifier::Crosshair(entity);
	//Sets whether this entity is the crosshair
	id.SetIsCrosshair(crosshair);
}

void ECS::SetIsGunTrail(unsigned entity, bool guntrail)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets guntrail entity
	EntityIdentifier::GunTrail(entity);
	//Sets whether this entity is the guntrail
	id.SetIsGunTrail(guntrail);
}

void ECS::SetIsHealthPack(unsigned entity, bool healthpack)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//Sets healthback entity
	EntityIdentifier::HealthPack(entity);
	//Sets whether this entity is the healthpack
	id.SetIsHealthPack(healthpack);
}

void ECS::SetIsAmmoCount10s(unsigned entity, bool ammocount10)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//sets ammo count 10s digit entity
	EntityIdentifier::AmmoCount10s(entity);
	//Sets wheter this entity is the 10s counter for ammo
	id.SetIsAmmoCounts10s(ammocount10);
}

void ECS::SetIsAmmoCount1s(unsigned entity, bool ammocount1)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//sets ammo count 1s digit entity
	EntityIdentifier::AmmoCount1s(entity);
	//Sets wheter this entity is the 1s counter for ammo
	id.SetIsAmmoCount1s(ammocount1);
}

void ECS::SetIsHealthBar(unsigned entity, bool healthbar)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//sets healtbar entity
	EntityIdentifier::Healthbar(entity);
	//Sets wheter this entity is the healthbar
	id.SetIsHealthbar(healthbar);
}

void ECS::SetIsManaBar(unsigned entity, bool manabar)
{
	//Gets reference to the component
	auto& id = GetComponent<EntityIdentifier>(entity);
	//sets manabar entity
	EntityIdentifier::Manabar(entity);
	//Sets wheter this entity is the manabar
	id.SetIsHealthbar(manabar);
}
