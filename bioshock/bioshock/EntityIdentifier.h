#ifndef __ENTITYIDENTIFIER_H__
#define __ENTITYIDENTIFIER_H__

#include "JSON.h"

class EntityIdentifier
{
public:
	//Adds the bit identifier to the whole identifier
	void AddComponent(unsigned int component);

	//Getters
	//Gets main player entity
	static unsigned int MainPlayer();
	bool GetIsMainPlayer() const;
	//Gets main camera entity
	static unsigned int MainCamera();
	bool GetIsMainCamera() const;
	//Gets crosshair 
	static unsigned int Crosshair(); 
	bool GetIsCrosshair() const; 
	//Gets gun trail 
	static unsigned int GunTrail(); 
	bool GetIsGunTrail() const; 
	//Gets health pack 
	static unsigned int HealthPack(); 
	bool GetIsHealthPack(); 
	//Get ammo counters
	static unsigned int AmmoCount10s(); 
	bool GetIsAmmoCount10s(); 
	static unsigned int AmmoCount1s(); 
	bool GetIsAmmoCount1s(); 
	//Get bars
	static unsigned int HealthBar();
	bool GetIsHealthBar();
	static unsigned int ManaBar();
	bool GetIsManaBar();
	//Get lightning
	static unsigned int Lightning();
	bool GetIsLightning();

	//Get entity number
	unsigned int GetEntity() const;
	//Get identifier bitfield
	unsigned int GetIdentifier() const;
	//Get Name
	std::string GetName() const;
	//Get if this entity is selected
	bool& GetSelected();
	//Gets the actual bit for the specified type
	static unsigned int CameraBit();
	static unsigned int SpriteBit();
	static unsigned int TransformBit();
	static unsigned int AnimationBit();
	static unsigned int LinkBit();
	static unsigned int PhysicsBit();
	static unsigned int HoriScrollCameraBit(); 
	static unsigned int VertScrollCameraBit(); 
	static unsigned int HudAspectBit();
	static unsigned int EnResourcesBit();

	//Setters
	//Sets main player entity
	static void MainPlayer(unsigned int entity);
	void SetIsMainPlayer(bool main);
	//Sets main camera entity
	static void MainCamera(unsigned int entity);
	void SetIsMainCamera(bool main);
	//Sets crosshair entity
	static void Crosshair(unsigned int entity); 
	void SetIsCrosshair(bool main);
	//Sets guntrail entity 
	static void GunTrail(unsigned int entity); 
	void SetIsGunTrail(bool main); 
	//Sets healthpack entity
	static void HealthPack(unsigned int entity); 
	void SetIsHealthPack(bool main);
	//Sets ammo counters
	static void AmmoCount10s(unsigned int entity); 
	void SetIsAmmoCounts10s(bool main); 
	static void AmmoCount1s(unsigned int entity); 
	void SetIsAmmoCount1s(bool main);
	//Sets bars
	static void Healthbar(unsigned int entity);
	void SetIsHealthbar(bool main);
	static void Manabar(unsigned int entity);
	void SetIsManabar(bool main);
	//Set lightning
	static void Lightning(unsigned int entity); 
	void SetIsLightning(bool main);

	void SetIsEntity(bool main);
	//Set entity number
	void SetEntity(unsigned int entity);
	//Set identifier bitfield
	void SetIdentifier(unsigned int identity);
	//Set the name
	void SetName(std::string name);
	//Set whether this entity is selected
	void SetSelected(bool selected);

private:
	//Main player
	static unsigned int m_mainPlayer;
	bool m_isMainPlayer = false;
	//Main camera
	static unsigned int m_mainCamera;
	bool m_isMainCamera = false;
	//Crosshair 
	static unsigned int m_crosshair; 
	bool m_isCrosshair; 
	//Gun trail 
	static unsigned int m_guntrail; 
	bool m_isGuntrail; 
	//Healthpacks
	static unsigned int m_healthpack;
	bool m_isHealthpack;
	//both ammo counters
	static unsigned int m_ammocount10s; 
	bool m_isAmmocount10s; 
	static unsigned int m_ammocount1s; 
	bool m_isAmmocount1s; 
	//bars
	static unsigned int m_healthbar;
	bool m_isHealthbar; 
	static unsigned int m_manabar;
	bool m_isManabar;
	//lightning
	static unsigned int m_lightning;
	bool m_isLightning; 

	//Stores the entity number
	unsigned int m_entity;
	//Stores the bit(s) of the types attached to this entity
	unsigned int m_identifier;

	//Stores the name
	std::string m_name = "";
	//Stores if this entity is selected
	bool m_selected = false;

	//Stores the bit for the specified type
	static unsigned int m_cameraBit;
	static unsigned int m_spriteBit;
	static unsigned int m_transformBit;
	static unsigned int m_animationBit;
	static unsigned int m_linkBit;
	static unsigned int m_physicsBit;
	static unsigned int m_horiScrollCameraBit; 
	static unsigned int m_vertScrollCameraBit; 
	static unsigned int m_hudAspectBit; 
	static unsigned int m_enResourcesBit;
};

#ifndef __ENTITYIDENTIFIERJSON_H__
#define __ENTITYIDENTIFIERJSON_H__

//Sends animation TO json file
inline void to_json(nlohmann::json& j, const EntityIdentifier& id)
{
	//Stores the identifier so that later I can know exactly what components are attached to each entity
	j["Identifier"] = id.GetIdentifier();

	//Stores whether or not this is the main camera
	j["MainCamera"] = id.GetIsMainCamera();

	//Stores whether or not this is the main player
	j["MainPlayer"] = id.GetIsMainPlayer();

	//Stores the name of this entity
	j["Name"] = id.GetName();
}

//Reads animation in FROM json file
inline void from_json(const nlohmann::json& j, EntityIdentifier& id)
{
	//Grab the identifier
	id.SetIdentifier(j["Identifier"]);

	//Grabs whether or not this is the main camera
	id.SetIsMainCamera(j["MainCamera"]);

	//Grabs whether or not this is the main player
	id.SetIsMainPlayer(j["MainPlayer"]);

	//Grabs the name of this entity
	id.SetName(j["Name"]);
}

#endif // !__ENTITYIDENTIFIERJSON_H__


#endif // !__ENTITYIDENTIFIER_H__
