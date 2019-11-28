#include "Game.h"

#include <random>



Game::~Game()
{
	//If window isn't equal to nullptr
	if (m_window != nullptr)
	{
		//Delete window
		delete m_window;
		//set window to nullptr
		m_window = nullptr;
	}

	//Goes through the scenes and deletes them
	for (unsigned i = 0; i < m_scenes.size(); i++)
	{
		if (m_scenes[i] != nullptr)
		{
			delete m_scenes[i];
			m_scenes[i] = nullptr;
		}
	}
}

void Game::InitGame()
{
	//Scene names and clear colors
	m_name = "Hello World";
	m_clearColor = vec4(0.15f, 0.33f, 0.58f, 1.f);

	//Initializes the backend
	BackEnd::InitBackEnd(m_name);

	//Grabs the initialized window
	m_window = BackEnd::GetWindow();

	//Creates a new test scene
	m_scenes.push_back(new TestScene("Test Scene")); 

	//sets active scene reference to the the test scene 
	m_activeScene = m_scenes[m_currentScene];

	//initiliazes the scene 
	m_activeScene->InitScene(float(BackEnd::GetWindowWidth()), float(BackEnd::GetWindowHeight())); 

	//Sets m_register to point to the register in the active scene 
	m_register = m_activeScene->GetScene(); 

	EffectManager::CreateEffect(Vignette, BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());; 
}

bool Game::Run()
{
	//While window is still open
	while (m_window->isOpen())
	{
		//Clear window with clearColor
		m_window->Clear(m_clearColor);
		
		//Updates the game
		Update();
		//Draws the game
		BackEnd::Draw(m_register);

		//Draws ImGUI
		if (m_guiActive)
			GUI();
		
		//Flips the windows
		m_window->Flip();
		
		//Polls events and then checks them
		BackEnd::PollEvents(m_register, &m_close, &m_motion, &m_click, &m_wheel);
		CheckEvents();

		//does the window have keyboard focus?
		if (Input::m_windowFocus)
		{
			//Accept all input
			AcceptInput();
		}
		//swaps to the approriate scene, might need to change later
		if (m_currentScene != m_sceneRunning) {
			m_sceneRunning = m_currentScene; 
			m_activeScene = m_scenes[m_currentScene]; 
			m_register = m_activeScene->GetScene();
		}
	}

	return true;
}

void Game::Update()
{
	//Update timer
	Timer::Update();
	//Update the backend
	BackEnd::Update(m_register);

	m_activeScene->Update(); 
}

void Game::GUI()
{
	UI::Start(BackEnd::GetWindowWidth(), BackEnd::GetWindowHeight());

	ImGui::Text("Place your different tabs below.");

	if (ImGui::BeginTabBar(""))
	{
		BackEnd::GUI(m_register, m_activeScene);

		ImGui::EndTabBar();
	}

	UI::End();
}

void Game::CheckEvents()
{
	if (m_close)
		m_window->Close();

	if (m_motion) {
		MouseMotion(BackEnd::GetMotionEvent());
		m_activeScene->MouseMotion(BackEnd::GetMotionEvent());
	}
		

	if (m_click) {
		MouseClick(BackEnd::GetClickEvent());
		m_activeScene->MouseClick(BackEnd::GetClickEvent()); 
	}
		

	if (m_wheel) {
		MouseWheel(BackEnd::GetWheelEvent());
		m_activeScene->MouseWheel(BackEnd::GetWheelEvent()); 
	}
		
}

void Game::AcceptInput()
{
	XInputManager::Update(); 

	//Just calls all the other input functions 
	GamepadInput(); 

	KeyboardHold();
	KeyboardDown();
	KeyboardUp();

	m_activeScene->AcceptInput(); 

	//Resets the key flags
	//Must be done once per frame for input to work
	Input::ResetKeys();
}

void Game::GamepadInput()
{
	XInputController* tempCon;
	//Gamepad button stroked (pressed)
	for (int i = 0; i < 3; i++) {
		if (XInputManager::ControllerConnected(i))
		{
			tempCon = XInputManager::GetController(i); 
			tempCon->SetStickDeadZone(0.1f); 

			//If the controller is connected, we run the different input types 
			m_activeScene->GamepadInput(tempCon); 
		}
	}
}

void Game::KeyboardHold()
{
}

void Game::KeyboardDown()
{
	//Keyboard button down

	//for main game only
	if (m_currentScene == 0) {		
		//esc, currently exits game, will open pause menu later 
		if (Input::GetKeyDown(Key::Escape))
		{
			m_window->Close(); 
		}
	}
}

void Game::KeyboardUp()
{
	//ImGui stuff 
	if (Input::GetKeyUp(Key::F1))
	{
		if (!UI::m_isInit)
		{
			UI::InitImGUI();
		}
		m_guiActive = !m_guiActive;
	}
}

void Game::MouseMotion(SDL_MouseMotionEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));

		if (!ImGui::GetIO().WantCaptureMouse)
		{

		}
	}

	//Resets the enabled flag
	m_motion = false;
}

void Game::MouseClick(SDL_MouseButtonEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MousePos = ImVec2(float(evnt.x), float(evnt.y));
		ImGui::GetIO().MouseDown[0] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT));
		ImGui::GetIO().MouseDown[1] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT));
		ImGui::GetIO().MouseDown[2] = (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE));
	}

	//Resets the enabled flag
	m_click = false;
}

void Game::MouseWheel(SDL_MouseWheelEvent evnt)
{
	if (m_guiActive)
	{
		ImGui::GetIO().MouseWheel = float(evnt.y);
	}
	//Resets the enabled flag
	m_wheel = false;
}
