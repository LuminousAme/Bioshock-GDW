#include "TestScene.h"

TestScene::TestScene(std::string name)
	: Scene(name)
{
}

void TestScene::InitScene(float windowWidth, float windowHeight)
{
	//dynamically allocate register, so it can be unloaded when we switch between scenes 
	m_sceneReg = new entt::registry;

	//Attach the register 
	ECS::AttachRegister(m_sceneReg); 

	//Set up aspect ratio 
	float aspectRatio = windowWidth / windowHeight; 

	//setup main camera 
	{
		//create the camera 
		auto entity = ECS::CreateEntity(); 
		EntityIdentifier::MainCamera(entity); 

		//Creates new orthographic camera 
		ECS::AttachComponent<Camera>(entity); 
		//attachs horizontal and vertical scrolling components 
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);

		//sets up camera
		vec4 temp = ECS::GetComponent<Camera>(entity).GetOrthoSize(); 
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Sets up scrolls
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<HorizontalScroll>(entity).SetOffSet(1.f); 
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetOffSet(1.f);

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::CameraBit() | EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::VertScrollCameraBit(); 
		ECS::SetUpIdentifier(entity, bitHolder, "Main Camera"); 
		ECS::SetIsMainCamera(entity, true); 
	}

	//setup new entity, Splicer Female
	{
		//Our animation file 
		auto animation = File::LoadJSON("LittleSister.json");

		//create new entity 
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "LittleSisterSpritesheet.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);

		animController.InitUVs(fileName);

		//Adds walking animation
		animController.AddAnimation(animation["Walk(woNeedle)"]); //index 0
		//Adds attacking animation
		animController.AddAnimation(animation["Walk"]); //index 1
		//Adds death animation
		animController.AddAnimation(animation["Base"]); //index 2 
		//Adds shock animation
		animController.AddAnimation(animation["Base(woNeedle)"]); //index 3

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 15, 15, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-50.f, 24.f, 99.f));

		//Sets up identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Little Sister");
	}
	//Set up the main player
	{
		//Our animation file 
		auto animations = File::LoadJSON("JackAnimations.json");

		//create new entity 
		auto entity = ECS::CreateEntity();
		EntityIdentifier::MainPlayer(entity);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "jack spritesheet.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);
		animController.InitUVs(fileName);
		//Adds walking with wrench animation
		animController.AddAnimation(animations["WrenchBase"]); //index 0
		//Adds walking with gun animation
		animController.AddAnimation(animations["GunWalk"]); //index 1
		//Adds attacking power with wrench animation 
		animController.AddAnimation(animations["WrenchPower"]); //index 2 
		//Adds attacking power with gun animation 
		animController.AddAnimation(animations["GunPower"]); //index 3
		//Adds attack with wrench 
		animController.AddAnimation(animations["WrenchSwing"]); //index 4
		//Adds firing the gun 
		animController.AddAnimation(animations["GunFire"]); //index 5

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 24, 24, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 99.f));

		//Sets up identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Jack");
		ECS::SetIsMainPlayer(entity, true);
	}

	//setup new entity, Splicer	Male
	{
		//Our animation file 
		auto animation = File::LoadJSON("MaleSplicer.json");

		//create new entity 
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "SplicerSpritesheet.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);

		animController.InitUVs(fileName);

		//Adds walking animation
		animController.AddAnimation(animation["Attack"]); //index 0
		//Adds attacking animation
		animController.AddAnimation(animation["Base"]); //index 1
		//Adds death animation
		animController.AddAnimation(animation["Death"]); //index 2 
		//Adds shock animation
		animController.AddAnimation(animation["Electric"]); //index 3

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 25, 15, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(33.f, 44.f, 99.f));

		//Sets up identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Male Splicer");
	}

	//setup new entity, Splicer Female
	{
		//Our animation file 
		auto animation = File::LoadJSON("FemaleSplicer.json");

		//create new entity 
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "FemaleSplicerSpritesheet.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);

		animController.InitUVs(fileName);

		//Adds walking animation
		animController.AddAnimation(animation["Attack"]); //index 0
		//Adds attacking animation
		animController.AddAnimation(animation["Base"]); //index 1
		//Adds death animation
		animController.AddAnimation(animation["Death"]); //index 2 
		//Adds shock animation
		animController.AddAnimation(animation["Electric"]); //index 3

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 21, 21, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-50.f, 50.f, 99.f));

		//Sets up identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Female Splicer");
	}

	//setup new entity, Big Daddy
	{
		//Our animation file 
		auto animation = File::LoadJSON("BigDaddy.json"); 

		//create new entity 
		auto entity = ECS::CreateEntity(); 
		
		//Add components
		ECS::AttachComponent<Sprite>(entity); 
		ECS::AttachComponent<Transform>(entity); 
		ECS::AttachComponent<AnimationController>(entity); 

		//Sets up components
		std::string fileName = "BigDaddySpritesheet.png"; 
		auto &animController = ECS::GetComponent<AnimationController>(entity); 
		
		animController.InitUVs(fileName);

		//Adds walking animation
		animController.AddAnimation(animation["Attack"]); //index 0
		//Adds attacking animation
		animController.AddAnimation(animation["Base"]); //index 1
		//Adds death animation
		animController.AddAnimation(animation["Death"]); //index 2 
		//Adds shock animation
		animController.AddAnimation(animation["Electric"]); //index 3

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 30, 30, true, &animController); 
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-10.f, 50.f, 99.f));

		//Sets up identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Big Daddy"); 
	}

	//setup a background image entity
	{
		auto animation = File::LoadJSON("Map.json");

		//create new entity 
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);

		//Sets up components
		std::string fileName = "map design.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);

		animController.InitUVs(fileName);

		//Adds Level One animation
		animController.AddAnimation(animation["LevelOne"]); //index 0
		//Adds Level Two animation
		animController.AddAnimation(animation["LevelTwo"]); //index 1
		//Adds Level Three animation
		animController.AddAnimation(animation["LevelThree"]); //index 2 

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 600, 525, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 98.f));

		//Sets up identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Big Daddy");
	}

	//Makes the camera focus on the main player
	//We do this at the very button to get the most accurate pointer to our transform
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

void TestScene::Update() {
	//display the effects 
	VignetteEffect* tempVig = (VignetteEffect*)EffectManager::GetEffect(EffectManager::GetVignetteHandle());
	tempVig->SetInnerRadius(0.01f);
	tempVig->SetOuterRadius(0.6f);
	tempVig->SetOpacity(1.f);

	//moves the player
	mainPlayerMove();


	//grab a reference to the main player's animations
	auto &animController = ECS::GetComponent<AnimationController>(EntityIdentifier::MainPlayer());
	//WEAPON SWITCHING 

	//switches the animation for which weapon is currently running 
	if (weaponSwitch && (animController.GetActiveAnim() == 0 || animController.GetActiveAnim() == 1)) {
		//if it's on the wrench 
		if (animController.GetActiveAnim() == 0) {
			//switch to the gun 
			animController.SetActiveAnim(1);
			currentWeapon = 1;
		}
		//otherwise it must be on the gun 
		else {
			//so switch to the wrench 
			animController.SetActiveAnim(0);
			currentWeapon = 0;
		}
		//set the switching flag, and flag to allow switch again to false 
		weaponSwitch = false;
		allowSwitchAgain = false;
	}

	//update the time since last switch up to 0.2 seconds, then reset it and allow the weapon to be switched again 
	if (allowSwitchAgain == false && timeSinceLastSwitch < 0.2f) {
		timeSinceLastSwitch += Timer::deltaTime;
	}
	else if (allowSwitchAgain == false && timeSinceLastSwitch >= 0.2f) {
		allowSwitchAgain = true;
		timeSinceLastSwitch = 0;
	}

	//WEAPON ATTACKING

	//if the player has inputed an attack 
	if (attack) {
		//check if there's a controller connected
		bool controllerConnected = false;
		int controllerIndex = 0;
		for (int i = 0; i < 3; i++) {
			if (XInputManager::ControllerConnected(i))
			{
				//if there is save it's index 
				controllerConnected = true;
				controllerIndex = i;
			}
		}

		//if there is a controller connected
		if (controllerConnected) {
			//grab a reference to it 
			XInputController* tempCon;
			tempCon = XInputManager::GetController(controllerIndex);
			//and make it begin rumbling 
			tempCon->SetRumble(controllerIndex, 20000);
		}

		//set the input flag to false
		attack = false;
		//and the in progress flag to true 
		currentlyAttacking = true;
		//if it's the wrench animation
		if (animController.GetActiveAnim() == 0) {
			//begin swinging wrench
			animController.SetActiveAnim(4);
		}
		//if it's the gun animation
		else if (animController.GetActiveAnim() == 1) {
			//begin shooting gun 
			animController.SetActiveAnim(5);
		}
	}

	//if the attack in progress flag is true, but the animation has ended
	if (currentlyAttacking && animController.GetAnimation(animController.GetActiveAnim()).GetAnimationDone()) {
		//check if there's a controller connected
		bool controllerConnected = false;
		int controllerIndex = 0;
		for (int i = 0; i < 3; i++) {
			if (XInputManager::ControllerConnected(i))
			{
				//if there is save it's index 
				controllerConnected = true;
				controllerIndex = i;
			}
		}

		//if there is a controller connected
		if (controllerConnected) {
			//grab a reference to it 
			XInputController* tempCon;
			tempCon = XInputManager::GetController(controllerIndex);
			//and make it stop rumbling 
			tempCon->SetRumble(controllerIndex, 0);
			tempCon->SetIsRumbling(false);
		}

		animController.GetAnimation(animController.GetActiveAnim()).Reset();
		//set the flag to false
		currentlyAttacking = false;
		attack = false;
		//and reset to the animations for just holding the weapon 
		if (animController.GetActiveAnim() == 4) {
			animController.SetActiveAnim(0);
		}
		else {
			animController.SetActiveAnim(1);
		}
	}

	//SPECIAL ABILITIES

	//if the player has inputed a lightning attack 
	if (lightning) {
		//check if there's a controller connected
		bool controllerConnected = false;
		int controllerIndex = 0;
		for (int i = 0; i < 3; i++) {
			if (XInputManager::ControllerConnected(i))
			{
				//if there is save it's index 
				controllerConnected = true;
				controllerIndex = i;
			}
		}

		//if there is a controller connected
		if (controllerConnected) {
			//grab a reference to it 
			XInputController* tempCon;
			tempCon = XInputManager::GetController(controllerIndex);
			//and make it begin rumbling 
			tempCon->SetRumble(controllerIndex, 20000);
		}

		//set the input flag to false
		lightning = false;
		//and the in progress flag to true 
		currentlyLightning = true;
		//if it's the wrench animation
		if (animController.GetActiveAnim() == 0) {
			//begin shooting lighning 
			animController.SetActiveAnim(2);
		}
		//if it's the gun animation
		else if (animController.GetActiveAnim() == 1) {
			//begin shooting lighning 
			animController.SetActiveAnim(3);
		}
	}

	//if the lightning in progress flag is true, but the animation has ended
	if (currentlyLightning && animController.GetAnimation(animController.GetActiveAnim()).GetAnimationDone()) {
		//check if there's a controller connected
		bool controllerConnected = false;
		int controllerIndex = 0;
		for (int i = 0; i < 3; i++) {
			if (XInputManager::ControllerConnected(i))
			{
				//if there is save it's index 
				controllerConnected = true;
				controllerIndex = i;
			}
		}

		//if there is a controller connected
		if (controllerConnected) {
			//grab a reference to it 
			XInputController* tempCon;
			tempCon = XInputManager::GetController(controllerIndex);
			//and make it stop rumbling 
			tempCon->SetRumble(controllerIndex, 0);
			tempCon->SetIsRumbling(false);
		}

		animController.GetAnimation(animController.GetActiveAnim()).Reset();
		//set the flag to false
		currentlyLightning = false;
		attack = false;
		//and reset to the animations for just holding the weapon 
		if (animController.GetActiveAnim() == 2) {
			animController.SetActiveAnim(0);
		}
		else {
			animController.SetActiveAnim(1);
		}
	}
}

void TestScene::AcceptInput() {
	KeyboardHold(); 
	KeyboardDown();
}

void TestScene::GamepadInput(XInputController* con) {
	GamepadStroke(con); 
	GamepadStick(con);
	GamepadTrigger(con);
}

void TestScene::GamepadStroke(XInputController* con) {
	//Gamepad button button stroke (pressed)

	//right bumper changes between weapons
	if (con->IsButtonPressed(Buttons::RB) && allowSwitchAgain) {
		//switch weapons
		weaponSwitch = true;
	}
	//left bumper changes between special abilities 
	if (con->IsButtonPressed(Buttons::LB)) {
		//switch special abilites 
	}
}

void TestScene::GamepadStick(XInputController* con){
	//Gamepad stick stuffs
	Stick sticks[2];
	con->GetSticks(sticks);

	//Left stick, movement 
	//move left
	if (sticks[0].x < -0.1f) {
		directionx = 1;
	}
	//move right
	else if (sticks[0].x > 0.1f) {
		directionx = 2;
	}
	//move down
	if (sticks[0].y < -0.1f) {
		directiony = 1;
	}
	//move up
	else if (sticks[0].y > 0.1f) {
		directiony = 2;
	}

	//If there's no input, slow down until we stop moving
	if (sticks[0].x > -0.1f && sticks[0].x < 0.1f) {
		directionx = 0;
	}
	if (sticks[0].y > -0.1f && sticks[0].y < 0.1f) {
		directiony = 0;
	}

	//Right stick, rotation
	if (sticks[1].x < -0.1f) {
		//rotate left
	}
	else if (sticks[1].x > 0.1f) {
		//rotate right 
	}
	else if (sticks[1].y < -0.1f) {
		//rotate "up"
	}
	else if (sticks[1].y > 0.1f) {
		//rotate "down" 
	}

}

void TestScene::GamepadTrigger(XInputController* con) {
	//Gamepad trigger stuff
	Triggers triggers;
	con->GetTriggers(triggers);

	if (triggers.RT > 0.5f && !attack && !currentlyAttacking) {
		//shoot gun or swing wrench 
		attack = true;
	}
	if (triggers.LT > 0.5f) {
		//fire off special ability 
		lightning = true;
	}
}

void TestScene::KeyboardHold() {
	//Keyboard button held

	//move up 
	if (Input::GetKey(Key::W) || Input::GetKey(Key::UpArrow))
	{
		directiony = 2;
	}
	//move down
	else if (Input::GetKey(Key::S) || Input::GetKey(Key::DownArrow))
	{
		directiony = 1;
	}
	//move left 
	if (Input::GetKey(Key::A) || Input::GetKey(Key::LeftArrow))
	{
		directionx = 1;
	}
	//move right 
	else if (Input::GetKey(Key::D) || Input::GetKey(Key::RightArrow))
	{
		directionx = 2;
	}

	//check if there's a controller connected
	bool controllerConnected = false;
	for (int i = 0; i < 3; i++) {
		if (XInputManager::ControllerConnected(i))
		{
			controllerConnected = true;
		}
	}

	//If there isn't, begin slowing down if there's no keyboard input (if there is a controller, the controller code does this for us already)
	if (controllerConnected == false) {
		if (!Input::GetKey(Key::D) && !Input::GetKey(Key::A) && !Input::GetKey(Key::LeftArrow) && !Input::GetKey(Key::RightArrow)) {
			directionx = 0;
		}

		if (!Input::GetKey(Key::W) && !Input::GetKey(Key::S) && !Input::GetKey(Key::UpArrow) && !Input::GetKey(Key::DownArrow)) {
			directiony = 0;
		}
	}
}

void TestScene::KeyboardDown() {
	//Keyboard button down
	if (Input::GetKeyDown(Key::One))
	{
		//make the active special lightning 
	}
	if (Input::GetKeyDown(Key::Two)) {
		//make the active special fire
	}
}

void TestScene::MouseMotion(SDL_MouseMotionEvent evnt) {

}

void TestScene::MouseClick(SDL_MouseButtonEvent evnt) {
	//left click fire gun or swing wrench 
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT) && !attack && !currentlyAttacking) {
		//fire gun / swing wrench 
		attack = true;
	}
	//right click fire off the special ability
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
		//fire off special ability 
		lightning = true;
	}

}

void TestScene::MouseWheel(SDL_MouseWheelEvent evnt) {
	if (evnt.y != 0 && allowSwitchAgain) {
		//Set the main weapon to change
		weaponSwitch = true;
	}
}

void TestScene::mainPlayerMove() {
	vec3 position = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).GetPosition();

	//calculates accleration 
	vec2 acceleration = vec2(0.f, 0.f);

	//Left stick, movement 
	if (directionx == 1) {
		acceleration.x = -20.f;
	}
	else if (directionx == 2) {
		acceleration.x = 20.f;
	}
	//stop moving left/right
	else {
		acceleration.x = 0;
		if (m_velocity.x > 0 && m_velocity.x >= 0.8f) {
			m_velocity.x -= 0.8f;
		}
		else if (m_velocity.x < 0 && m_velocity.x <= -0.8f) {
			m_velocity.x += 0.8f;
		}
		else {
			m_velocity.x = 0;
		}
	}

	if (directiony == 1) {
		acceleration.y = -20.f;
	}
	else if (directiony == 2) {
		acceleration.y = 20.f;
	}
	//stop moving up/down
	else {
		acceleration.y = 0;
		if (m_velocity.y > 0 && m_velocity.y >= 0.8f) {
			m_velocity.y -= 0.8f;
		}
		else if (m_velocity.y < 0 && m_velocity.y <= -0.8f) {
			m_velocity.y += 0.8f;
		}
		else {
			m_velocity.y = 0;
		}
	}

	//Update velocity if not over max 
	//x-axis 
	if (m_velocity.x < -31.f)
	{
		m_velocity.x = -30.8f;
	}
	else if (m_velocity.x > 31.f)
	{
		m_velocity.x = 30.8f;
	}
	else {
		m_velocity.x = m_velocity.x + (acceleration.x * Timer::deltaTime);
	}
	//y-axis 
	if (m_velocity.y < -31.f)
	{
		m_velocity.y = -30.8f;
	}
	else if (m_velocity.y > 31.f)
	{
		m_velocity.y = 30.8f;
	}
	else {
		m_velocity.y = m_velocity.y + (acceleration.y * Timer::deltaTime);
	}

	//Updates position 
	position = position + (vec3(m_velocity.x, m_velocity.y, 0.f) * Timer::deltaTime) +
		(vec3(acceleration.x, acceleration.y, 0.f) * (0.5f) * (Timer::deltaTime * Timer::deltaTime));

	//Sets updated position 
	ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()).SetPosition(position);
}