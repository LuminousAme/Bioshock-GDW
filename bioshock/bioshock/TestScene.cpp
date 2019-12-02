#include "TestScene.h"

TestScene::TestScene(std::string name)
	: Scene(name)
{
	m_gravity = b2Vec2(float32(0.f), float32(0.f)); 
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
		ECS::GetComponent<HorizontalScroll>(entity).SetOffSet(0.0001f);
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetOffSet(0.0001f);

		//Matches the camera to main player spawn
		ECS::GetComponent<Camera>(entity).SetPosition(vec3(120.f, -15.f, ECS::GetComponent<Camera>(entity).GetPositionZ()));

		//Sets up the Identifier
		unsigned int bitHolder = EntityIdentifier::CameraBit() | EntityIdentifier::HoriScrollCameraBit() | EntityIdentifier::VertScrollCameraBit(); 
		ECS::SetUpIdentifier(entity, bitHolder, "Main Camera"); 
		ECS::SetIsMainCamera(entity, true); 
	}

	//steup new entity, mainplayer
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
		ECS::AttachComponent<PhysicsBody>(entity); 
		ECS::AttachComponent<EnResources>(entity);

		//Sets up components
		std::string fileName = "jack spritesheet.png"; 
		auto &animController = ECS::GetComponent<AnimationController>(entity); 
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

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 48, true, &animController); 
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(120.f, -15.f, 75.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity); 
		auto& tempPhysBod = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);

		b2Body* tempBody; 
		b2BodyDef tempDef; 
		tempDef.type = b2_dynamicBody; 
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY())); 

		tempBody = m_physicsWorld->CreateBody(&tempDef); 

		tempPhysBod = PhysicsBody(tempBody, float(tempSpr.GetWidth() * 0.4f), float(tempSpr.GetHeight() * 0.4f),
			vec2(0.f, 0.f), false);

		const char* UD[] = { "Player" };
		tempPhysBod.GetBody()->SetUserData(UD);


		//Sets up identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit() | EntityIdentifier::PhysicsBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Jack"); 
		ECS::SetIsMainPlayer(entity, true); 
	}

	//Setup UI (Crosshair) entity
	{
		//Creates entity
		auto entity = ECS::CreateEntity(); 

		//Adds components 
		ECS::AttachComponent<Sprite>(entity); 
		ECS::AttachComponent<Transform>(entity); 

		//Sets up components 
		std::string fileName = "crosshair.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 2, 2); 

		ECS::GetComponent<Transform>(entity).SetPosition(50, 0, 99.f);


		//Sets up identitifer
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Crosshair");
		ECS::SetIsCrosshair(entity, true); 
	}

	//Setup UI (health bar surrond) entity 
	{
		//Creates entity 
		auto entity = ECS::CreateEntity(); 

		//Adds components
		ECS::AttachComponent<Sprite>(entity); 
		ECS::AttachComponent<Transform>(entity); 
		ECS::AttachComponent<HudAspect>(entity);

		//Sets up components 
		std::string fileName = "HealthUI.png"; 
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 96, 96);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-140.f, 55.f, 99.01f)); 
		ECS::GetComponent<HudAspect>(entity).setHudAdjust(vec2(-140.f, 55.f));

		//Sets up identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::HudAspectBit(); 
		ECS::SetUpIdentifier(entity, bitHolder, "Health bar surrond UI");
	}

	//Setup UI (mana bar surrond) entity
	{
		//Create entity
		auto entity = ECS::CreateEntity(); 

		//Adds components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<HudAspect>(entity);

		//Sets up components 
		std::string fileName = "ManaUI.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 96, 96);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-133.f, 45.f, 99.02f));
		ECS::GetComponent<HudAspect>(entity).setHudAdjust(vec2(-133.f, 45.f));

		//Sets up identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::HudAspectBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Mana bar surrond UI");
	}

	//Setup UI (health and mana bars) entities
	for (int i = 0; i < 2; i++)
	{
		{
			//Our animation file 
			auto bars = File::LoadJSON("bars.json");

			//Create entity
			auto entity = ECS::CreateEntity();

			//Sets up components 
			std::string fileName; 
			if(i == 0) fileName = "HealthBar.png";
			else fileName = "ManaBar.png";

			//Adds components
			ECS::AttachComponent<Sprite>(entity); 
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<HudAspect>(entity);
			ECS::AttachComponent<AnimationController>(entity);

			auto& animController = ECS::GetComponent<AnimationController>(entity);
			animController.InitUVs(fileName);
			//Adds 0
			animController.AddAnimation(bars["0"]); //index 0
			//Adds 1
			animController.AddAnimation(bars["1"]); //index 1
			//Adds 2
			animController.AddAnimation(bars["2"]); //index 2 
			//Adds 3
			animController.AddAnimation(bars["3"]); //index 3
			//Adds 4
			animController.AddAnimation(bars["4"]); //index 4
			//Adds 5
			animController.AddAnimation(bars["5"]); //index 5
			//Adds 6
			animController.AddAnimation(bars["6"]); //index 6
			//Adds 7
			animController.AddAnimation(bars["7"]); //index 7
			//Adds 8
			animController.AddAnimation(bars["8"]); //index 8 
			//Adds 9
			animController.AddAnimation(bars["9"]); //index 9
			//Adds 10
			animController.AddAnimation(bars["10"]); //index 10
			//Adds 11
			animController.AddAnimation(bars["11"]); //index 11
			//Adds 12
			animController.AddAnimation(bars["12"]); //index 12 

			animController.SetActiveAnim(12);
			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 120, true, &animController);

			if (i == 0)
			{
				ECS::GetComponent<Transform>(entity).SetPosition(vec3(-143.f, 65.f, 99.03f));
				ECS::GetComponent<HudAspect>(entity).setHudAdjust(vec2(-143.f, 65.f));
			}
			else
			{
				ECS::GetComponent<Transform>(entity).SetPosition(vec3(-133.f, 52.f, 99.04f));
				ECS::GetComponent<HudAspect>(entity).setHudAdjust(vec2(-133.f, 52.f));
			}

			//Sets up identifier
			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::HudAspectBit()
				| EntityIdentifier::AnimationBit();
			
			if (i == 0)
			{
				ECS::SetUpIdentifier(entity, bitHolder, "Healthbar");
				ECS::SetIsHealthBar(entity, true);
			}
			else
			{
				ECS::SetUpIdentifier(entity, bitHolder, "Manabar");
				ECS::SetIsManaBar(entity, true);
			}

		}
	}

	//Setup UI (bumbers for ammo and healthpacks) entity
	{
		//Create entity
		auto entity = ECS::CreateEntity(); 

		//Adds components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<HudAspect>(entity);

		//Sets up componetns
		std::string fileName = "ammo and health packs bumper.png"; 
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 48, 48);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(145.f, -70.f, 99.05));
		ECS::GetComponent<HudAspect>(entity).setHudAdjust(vec2(145.f, -70.f));

		//Sets up identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::HudAspectBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Resource bumper");
	}

	//Setup UI (num counters for ammo and healthpacks) entity 
	for (int i = 0; i < 3; i++)
	{
		{
			//Our animation (digits file 
			auto nums = File::LoadJSON("numbers.json");

			//Create entity
			auto entity = ECS::CreateEntity();

			//Adds components 
			ECS::AttachComponent<Sprite>(entity);
			ECS::AttachComponent<Transform>(entity);
			ECS::AttachComponent<AnimationController>(entity);
			ECS::AttachComponent<HudAspect>(entity);

			//Sets up components 
			std::string fileName = "numbers.png";

			auto& animController = ECS::GetComponent<AnimationController>(entity);
			animController.InitUVs(fileName);
			//Adds 0
			animController.AddAnimation(nums["0"]); //index 0
			//Adds 1
			animController.AddAnimation(nums["1"]); //index 1
			//Adds 2
			animController.AddAnimation(nums["2"]); //index 2 
			//Adds 3
			animController.AddAnimation(nums["3"]); //index 3
			//Adds 4
			animController.AddAnimation(nums["4"]); //index 4
			//Adds 5
			animController.AddAnimation(nums["5"]); //index 5
			//Adds 6
			animController.AddAnimation(nums["6"]); //index 6
			//Adds 7
			animController.AddAnimation(nums["7"]); //index 7
			//Adds 8
			animController.AddAnimation(nums["8"]); //index 8 
			//Adds 9
			animController.AddAnimation(nums["9"]); //index 9

			animController.SetActiveAnim(0);

			ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 10, true, &animController);

			if (i == 0)
			{
				ECS::GetComponent<Transform>(entity).SetPosition(vec3(152.f, -72.f, 99.06f));
				ECS::GetComponent<HudAspect>(entity).setHudAdjust(vec2(152.f, -72.f));
			}
			else if (i == 1)
			{
				ECS::GetComponent<Transform>(entity).SetPosition(vec3(153.f, -88.f, 99.07f));
				ECS::GetComponent<HudAspect>(entity).setHudAdjust(vec2(153.f, -88.f));
			}
			else {
				ECS::GetComponent<Transform>(entity).SetPosition(vec3(158.f, -88.f, 99.08f));
				ECS::GetComponent<HudAspect>(entity).setHudAdjust(vec2(158.f, -88.f));
			}
		
			//Sets up identifier
			unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::HudAspectBit()
				| EntityIdentifier::AnimationBit();
			ECS::SetUpIdentifier(entity, bitHolder, "HUD number" + std::to_string(i+1));
			if (i == 0) ECS::SetIsHealthPack(entity, true);
			else if (i == 1) ECS::SetIsAmmoCount10s(entity, true);
			else ECS::SetIsAmmoCount1s(entity, true);
		}
	}
	

	//Setup gun trail entity 
	{
		//Creates entity 
		auto entity = ECS::CreateEntity(); 

		//Adds components 
		ECS::AttachComponent<Sprite>(entity); 
		ECS::AttachComponent<Transform>(entity); 

		//Sets up components 
		std::string fileName = "gun trail.png";
		ECS::GetComponent <Sprite>(entity).LoadSprite(fileName, 200, 48); 

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-10000.f, -10000.f, 52.f)); 

		//Sets up identifier
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit(); 
		ECS::SetUpIdentifier(entity, bitHolder, "Gun trail");
		ECS::SetIsGunTrail(entity, true); 
	}

	//setup new entity, Lightning
	{
		//Our animation file 
		auto animation = File::LoadJSON("ElectricShock.json");

		//create new entity 
		auto entity = ECS::CreateEntity();

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<AnimationController>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up components
		std::string fileName = "Lightning.png";
		auto& animController = ECS::GetComponent<AnimationController>(entity);

		animController.InitUVs(fileName);

		//Adds Shock animation
		animController.AddAnimation(animation["Shock"]); //index 0

		animController.SetActiveAnim(0);

		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 15, 4, true, &animController);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(-10000.f, -1000.f, 99.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhysBod = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhysBod = PhysicsBody(tempBody, float(tempSpr.GetWidth()), float(tempSpr.GetHeight()),
			vec2(0.f, 0.f), false);

		const char* UD[] = { "Lightning" };
		tempPhysBod.GetBody()->SetUserData(UD);

		//Sets up identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Lightning");
		ECS::SetIsLightning(entity, true);
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
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 0.f, 2.f));

		//Sets up identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "Map");
	}

	//setup map collisions, water right of spawn
	/*
	{
		//create the entity
		auto entity = ECS::CreateEntity(); 

		//Adds components 
		ECS::AttachComponent<Transform>(entity); 
		ECS::AttachComponent<PhysicsBody>(entity);

		ECS::GetComponent<Transform>(entity).SetPosition(vec3(220.f, 12.f, 2.01f));

		auto& tempPhysBod = ECS::GetComponent<PhysicsBody>(entity);
		auto& tempTrans = ECS::GetComponent<Transform>(entity);

		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(tempTrans.GetPositionX()), float32(tempTrans.GetPositionY()));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhysBod = PhysicsBody(tempBody, 160.f, 496.f, vec2(0.f, 0.f), false);

		const char* UD[] = { "Water" };
		tempPhysBod.GetBody()->SetUserData(UD);

		//Sets up identifier 
		unsigned int bitHolder = EntityIdentifier::SpriteBit() | EntityIdentifier::TransformBit() | EntityIdentifier::AnimationBit();
		ECS::SetUpIdentifier(entity, bitHolder, "water 1");
		ECS::SetIsLightning(entity, true);
	} */
	

	//Makes the camera focus on the main player
	//We do this at the very button to get the most accurate pointer to our transform
	ECS::GetComponent<HorizontalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(EntityIdentifier::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()));
}

void TestScene::Update() {
	//hide the mouse (we only want the crosshair to display)
	ShowCursor(false);

	auto& playerTrans = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());
	printf("Player pos: %f, %f\n", playerTrans.GetPositionX(), playerTrans.GetPositionY());

	auto& pResources = ECS::GetComponent<EnResources>(EntityIdentifier::MainPlayer()); 
	//update the player resources HUD
	ECS::GetComponent<AnimationController>(EntityIdentifier::HealthPack()).SetActiveAnim(pResources.GetPacks()); //health packs count
	ECS::GetComponent<AnimationController>(EntityIdentifier::AmmoCount10s()).SetActiveAnim(pResources.GetAmmo() / 10 % 10); //10s digit for ammo
	ECS::GetComponent<AnimationController>(EntityIdentifier::AmmoCount1s()).SetActiveAnim(pResources.GetAmmo() % 10); //1s digit for ammo
	ECS::GetComponent<AnimationController>(EntityIdentifier::HealthBar()).SetActiveAnim(pResources.GetHP()); //player hp 
	ECS::GetComponent<AnimationController>(EntityIdentifier::ManaBar()).SetActiveAnim(pResources.GetMana()); //player mana

	//if the time since the last gunshot was fired is less than 0.15f, add deltaTime 
	if (timeSinceShotFired < 0.02f)
	{
		timeSinceShotFired += Timer::deltaTime; 
	}
	else
	{
		auto& gTrans = ECS::GetComponent<Transform>(EntityIdentifier::GunTrail());
		gTrans.SetPosition(vec3(-10000.f, -10000.f, gTrans.GetPositionZ())); 
		gTrans.SetRotationAngleZ(0); 
	}

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
		else if (animController.GetActiveAnim() == 1 && pResources.GetAmmo() > 0) {
			//begin shooting gun 
			animController.SetActiveAnim(5);
			fireGun = true;
		}
		else if (animController.GetActiveAnim() == 1 && pResources.GetAmmo() <= 0)
		{
			currentlyAttacking = false;
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
	if (lightning && pResources.GetMana() > 0) {
		//check if there's a controller connected
		bool controllerConnected = false;
		int controllerIndex = 0;

		//reduce the player's mana 
		pResources.SetMana(pResources.GetMana() - 1);

		//grab references to the player and lightning'ss transforms
		auto& pTrans = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());
		auto& lTrans = ECS::GetComponent<Transform>(EntityIdentifier::Lightning());

		//grab a reference to the lightning's physicsbody
		auto& lPhys = ECS::GetComponent<PhysicsBody>(EntityIdentifier::Lightning());

		//set the rotation of the lightning to match the players
		lTrans.SetRotationAngleZ(pTrans.GetRotationAngleZ());

		//set the lignhtning's position equal to the player
		lTrans.SetPosition(vec3(pTrans.GetPositionX() + directionFaced.x * 30, pTrans.GetPositionY() + directionFaced.y * 30, pTrans.GetPositionZ()));
		lPhys.GetBody()->SetTransform(b2Vec2(float32(lTrans.GetPositionX()), float32(lTrans.GetPositionY())),lPhys.GetBody()->GetAngle());

		lPhys.ApplyForce(vec3(INT_MAX * directionFaced.x, INT_MAX * directionFaced.y, 0));

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
	else if (lightning && pResources.GetMana() <= 0)
	{
		lightning = false;
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

	//grab a reference to the crosshair's transform 
	auto& pTrans = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer()); 
	auto& cTrans = ECS::GetComponent<Transform>(EntityIdentifier::Crosshair()); 

	//create a vector representing the crosshair (and the direction in which the gun should fire)
	vec2 tempVec = convertedMouse - directionFaced; 
	//get it's lenght
	float lenght = tempVec.GetMagnitude(); 

	//create a vector to adjust for the gun not being centered in jack's sprite (not perfect but helps quite a bit)
	vec2 diradjust = vec2(1.f, -0.15f); 

	//setup a rotation matrix with Jack's rotation
	mat2 rot = mat2(vec2(cos(pTrans.GetRotationAngleZ()), -sin(pTrans.GetRotationAngleZ())), vec2(sin(pTrans.GetRotationAngleZ()), cos(pTrans.GetRotationAngleZ())));
	//rotate the adjustment vector
	diradjust = rot * diradjust;

	//set the temp vector to be equal to the direction the player the player is faced, modified by the adjustment
	tempVec = (directionFaced + diradjust);

	//extend it back out to it's lenght 
	tempVec = tempVec * lenght; 

	//adjust it to the player's position (so when the player moves, the crosshair moves with them)
	tempVec = tempVec + vec2(pTrans.GetPositionX(), pTrans.GetPositionY()); 
	//set the crosshair's position
	cTrans.SetPosition(tempVec.x, tempVec.y, cTrans.GetPositionZ()); 

	//if the player has fired the gun
	if (fireGun) {
		//stop firing the gun
		fireGun = false; 

		//remove one ammo
		pResources.SetAmmo(pResources.GetAmmo() - 1);
		//Grab a reference to the gun's transform
		auto& gTrans = ECS::GetComponent<Transform>(EntityIdentifier::GunTrail());

		//Set the gun trail's rotation to match that of the player
		gTrans.SetRotationAngleZ(pTrans.GetRotationAngleZ()); 

		//create a temporary vector to move the sprite so it fires out of the gun
		vec2 temp2vec = vec2(115, 0); 

		//rotate said vector by the player's rotation angle
		temp2vec = rot * temp2vec; 
		
		//reset the position of the gun trail
		gTrans.SetPosition(vec3(pTrans.GetPositionX() + temp2vec.x, pTrans.GetPositionY() + temp2vec.y, gTrans.GetPositionZ()));

		//reset the timer between shots
		timeSinceShotFired = 0.f; 
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
	//X uses health packs 
	if (con->IsButtonPressed(Buttons::DPAD_DOWN)) {
		auto& pResources = ECS::GetComponent<EnResources>(EntityIdentifier::MainPlayer()); 
		if (pResources.GetPacks() > 0) {
			pResources.SetPacks(pResources.GetPacks() - 1); 
			pResources.SetHP(12);
		}
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

	vec2 nDirFace = directionFaced;

	//Right stick, rotation
	if (sticks[1].x < -0.1f) {
		//rotate left
		float angle = -0.1f;

		mat2 rot = mat2(vec2(cos(angle), -sin(angle)), vec2(sin(angle), cos(angle)));
		directionFaced = rot * directionFaced;


		//grab a reference to the main player's transform (so we can rotate the sprite) 
		auto& tempTrans = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());

		//add the existing sprite rotation to the new angle
		angle += tempTrans.GetRotationAngleZ();

		//set the sprite's rotation equal to the new angle 
		tempTrans.SetRotationAngleZ(angle);
	}
	else if (sticks[1].x > 0.1f) {
		//rotate right 
		float angle = 0.1f;

		mat2 rot = mat2(vec2(cos(angle), -sin(angle)), vec2(sin(angle), cos(angle)));
		directionFaced = rot * directionFaced;


		//grab a reference to the main player's transform (so we can rotate the sprite) 
		auto& tempTrans = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());

		//add the existing sprite rotation to the new angle
		angle += tempTrans.GetRotationAngleZ();

		//set the sprite's rotation equal to the new angle 
		tempTrans.SetRotationAngleZ(angle);
	}
	else if (sticks[1].y < -0.1f) {
		//rotate "up"
		float angle = 0.1f;

		mat2 rot = mat2(vec2(cos(angle), -sin(angle)), vec2(sin(angle), cos(angle)));
		directionFaced = rot * directionFaced;


		//grab a reference to the main player's transform (so we can rotate the sprite) 
		auto& tempTrans = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());

		//add the existing sprite rotation to the new angle
		angle += tempTrans.GetRotationAngleZ();

		//set the sprite's rotation equal to the new angle 
		tempTrans.SetRotationAngleZ(angle);
	}
	else if (sticks[1].y > 0.1f) {
		//rotate "down" 
		float angle = -0.1f;
		
		mat2 rot = mat2(vec2(cos(angle), -sin(angle)), vec2(sin(angle), cos(angle)));
		directionFaced = rot * directionFaced;


		//grab a reference to the main player's transform (so we can rotate the sprite) 
		auto& tempTrans = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());

		//add the existing sprite rotation to the new angle
		angle += tempTrans.GetRotationAngleZ();

		//set the sprite's rotation equal to the new angle 
		tempTrans.SetRotationAngleZ(angle);
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
	if (triggers.LT > 0.5f && !lightning && !currentlyLightning) {
		//fire off special ability 
		lightning = true;
	}
}

void TestScene::KeyboardHold() {
	//Keyboard button held
	if (Input::GetKey(Key::Control))
	{
		auto& MainCamera = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());

		if (Input::GetKey(Key::Z))
		{
			if (MainCamera.GetOrthoSize().x != -13 && MainCamera.GetOrthoSize().y != 13 && MainCamera.GetOrthoSize().z != -13)
				MainCamera.Zoom(1);
			//printf("Orthogonial Size: %f %c %f %c %f \n",MainCamera.GetOrthoSize().x, ',', MainCamera.GetOrthoSize().y, ',', MainCamera.GetOrthoSize().z);
		}

		if (Input::GetKey(Key::X))
		{
			auto& MainCamera = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
			MainCamera.Zoom(-1);
		}
	}

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
	auto& pResources = ECS::GetComponent<EnResources>(EntityIdentifier::MainPlayer());
	if (Input::GetKeyDown(Key::One)) {
		if (pResources.GetPacks() > 0) {
			pResources.SetPacks(pResources.GetPacks() - 1);
			pResources.SetHP(12);
		}
	}

	if (Input::GetKeyDown(Key::O)) {
		pResources.SetHP(pResources.GetHP() - 1);
		if (pResources.GetHP() == 0) {
			close = true;
		}
	}
}

void TestScene::MouseMotion(SDL_MouseMotionEvent evnt) {
	bool controller = false; 
	for (int i = 0; i < 3; i++) {
		if (XInputManager::ControllerConnected(i))
		{
			controller = true;
		}
	}
	if(!controller)
	{
		//grab a reference to the main camera (so rotation can still work even when zoomed in or out 
		auto& tempCam = ECS::GetComponent<Camera>(EntityIdentifier::MainCamera());
		//grab a reference to the main player's transform (so we can rotate the sprite) 
		auto& tempTrans = ECS::GetComponent<Transform>(EntityIdentifier::MainPlayer());

		//floats for the width and height of the screen, used to convert the mouse so we can rotate to follow the mouse 
		float width = tempCam.GetAspect() * (tempCam.GetOrthoSize().y - tempCam.GetOrthoSize().x);
		float height = (tempCam.GetOrthoSize().w - tempCam.GetOrthoSize().z);

		//grab the mouse pixel coordinates 
		convertedMouse = vec2(evnt.x, evnt.y); //not yet converted 
		//Convert them to world coordinates 
		mouseUtils::convertToGL(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight(), width, height, convertedMouse.x, convertedMouse.y); //now converted

		//rotate the mouse's global coordinates so that we can make the player's rotation follow the mouse 
		mat2 rot = mat2(vec2(cos(-1.5f), -sin(-1.5f)), vec2(sin(-1.5f), cos(-1.5f)));
		convertedMouse = rot * convertedMouse;

		//find the angle between the converted and rotated mouse and the direction the player is facing 
		float angle = convertedMouse.Dot(directionFaced) / (convertedMouse.GetMagnitude() * directionFaced.GetMagnitude()); //in radians

		//rotate the vector representing the direction the player is facing
		rot = mat2(vec2(cos(angle), -sin(angle)), vec2(sin(angle), cos(angle)));
		directionFaced = rot * directionFaced;

		//add the existing sprite rotation to the new angle
		angle += tempTrans.GetRotationAngleZ();

		//set the sprite's rotation equal to the new angle 
		tempTrans.SetRotationAngleZ(angle);
	}
	
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
	auto& tempPhysBod = ECS::GetComponent<PhysicsBody>(EntityIdentifier::MainPlayer()); 
	b2Body* body = tempPhysBod.GetBody(); 

	//Left stick, movement 
	if (directionx == 1 && body->GetLinearVelocity().x > float32(-40.f)) {
		tempPhysBod.ApplyForce(vec3(-8000.f, 0.f, 0.f));
	}
	else if (directionx == 2 && body->GetLinearVelocity().x < float32(40.f)) {
		tempPhysBod.ApplyForce(vec3(8000.f, 0.f, 0.f));
	}
	//stop moving left/right
	else {
		if (body->GetLinearVelocity().x > float32(0.f))
		{
			tempPhysBod.ApplyForce(vec3(-8000.f, 0.f, 0.f));
		}
		else if (body->GetLinearVelocity().x < float32(0.f))
		{
			tempPhysBod.ApplyForce(vec3(8000.f, 0.f, 0.f));
		}
	}

	if (directiony == 1 && body->GetLinearVelocity().y > float32(-40.f)) {
		tempPhysBod.ApplyForce(vec3(0.f, -8000.f, 0.f));
	}
	else if (directiony == 2 && body->GetLinearVelocity().y < float32(40.f)) {
		tempPhysBod.ApplyForce(vec3(0.f, 8000.f, 0.f));
	}
	//stop moving up/down
	else {
		if (body->GetLinearVelocity().y > float32(0.f))
		{
			tempPhysBod.ApplyForce(vec3(0.f, -8000.f, 0.f));
		}
		else if (body->GetLinearVelocity().y < float32(0.f))
		{
			tempPhysBod.ApplyForce(vec3(0.f, 8000.f, 0.f));
		}
	}
}