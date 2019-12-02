#pragma once

#include "JSON.h"

//resources for player and enemies (ammo, health, mana, healing pack, etc.) 
class EnResources
{
public:
	//creates the resource manager
	EnResources(); 
	//creates the resource manager with set values 
	EnResources(int h, int m, int a, int p); 
	//Destorys the resource manager
	~EnResources();

	//Getters
	int GetHP() const; 
	int GetMana() const;
	int GetAmmo() const; 
	int GetPacks() const; 

	//Setters
	void SetHP(int h); 
	void SetMana(int m); 
	void SetAmmo(int a); 
	void SetPacks(int p);

private:
	//health 
	int hp; 
	//mana
	int mana;
	//ammo
	int ammo; 
	//health packs
	int packs;
};

inline void to_json(nlohmann::json& j, const EnResources& r)
{
	j["Hp"] = r.GetHP(); 
	j["Mana"] = r.GetMana(); 
	j["Ammo"] = r.GetAmmo(); 
	j["Packs"] = r.GetPacks(); 
}

inline void from_json(const nlohmann::json& j, EnResources& r)
{
	r.SetHP(j["Hp"]); 
	r.SetMana(j["Mana"]); 
	r.SetAmmo(j["Ammo"]);
	r.SetPacks(j["Packs"]);
}
