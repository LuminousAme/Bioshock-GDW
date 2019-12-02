#include "EnResources.h"

EnResources::EnResources()
{
	hp = 12; 
	mana = 12;
	ammo = 20;
	packs = 1;
}

EnResources::EnResources(int h, int m, int a, int p)
{
	hp = h; 
	mana = m; 
	ammo = a; 
	packs = p;
}

EnResources::~EnResources()
{
}

int EnResources::GetHP() const
{
	return hp;
}

int EnResources::GetMana() const
{
	return mana;
}

int EnResources::GetAmmo() const
{
	return ammo;
}

int EnResources::GetPacks() const
{
	return packs;
}

void EnResources::SetHP(int h)
{
	hp = h; 
}

void EnResources::SetMana(int m)
{
	mana = m;
}

void EnResources::SetAmmo(int a)
{
	ammo = a;
}

void EnResources::SetPacks(int p)
{
	packs = p;
}
