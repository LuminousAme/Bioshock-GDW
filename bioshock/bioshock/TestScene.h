#pragma once

#include "Scene.h"
#include "Xinput.h"
#include "EffectManager.h"

class TestScene : public Scene
{
public:
	TestScene(std::string name); 

	//does not require override
	void Switch();
	void Attack();
	void SpecialAttack();
	bool WallCollision(vec3);

	void InitScene(float windowWidth, float windowHeight) override; 

	void Update() override; 
	void AcceptInput() override; 
	void GamepadInput(XInputController* con) override;

	void GamepadStroke(XInputController* con) override;
	void GamepadStick(XInputController* con) override;
	void GamepadTrigger(XInputController* con) override;
	void KeyboardHold() override;
	void KeyboardDown() override;

	//Mouse input
	void MouseMotion(SDL_MouseMotionEvent evnt) override;
	void MouseClick(SDL_MouseButtonEvent evnt) override;
	void MouseWheel(SDL_MouseWheelEvent evnt) override;

	//Move the main player
	void mainPlayerMove(); 
private:
	//main player velocity 
	vec2 m_velocity = vec2(0.f, 0.f);

	//main player direction
	int directionx = 0;
	int directiony = 0;

	//stuff for switching weapons 
	bool weaponSwitch = false;
	bool allowSwitchAgain = true;
	float timeSinceLastSwitch = 0.f;
	int currentWeapon = 0;

	//stuff for making attacks
	bool attack = false;
	bool currentlyAttacking = false;

	//Stuff for using abilities 
	bool lightning = false;
	bool currentlyLightning = false;
};