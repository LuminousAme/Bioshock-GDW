#pragma once

#include "Scene.h"
#include "Xinput.h"
#include "EffectManager.h"
#include "mouseUtils.h"

class TestScene : public Scene
{
public:
	TestScene(std::string name); 

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
	//main player movement direction
	int directionx = 0;
	int directiony = 0;

	//main player facing direction
	vec2 directionFaced = vec2(1.f, 0.f); 

	//stores mouse global coordinates 
	vec2 convertedMouse = vec2(0.f, 0.f); 

	//stuff for switching weapons 
	bool weaponSwitch = false;
	bool allowSwitchAgain = true;
	float timeSinceLastSwitch = 0.f;
	int currentWeapon = 0;

	//stuff for making attacks
	bool attack = false;
	bool currentlyAttacking = false;
	bool fireGun = false; 
	float timeSinceShotFired = 2.f; 

	//Stuff for using abilities 
	bool lightning = false;
	bool currentlyLightning = false;
};