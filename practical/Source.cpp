//	Ask the compiler to include minimal header files for our program.
#define WIN32_LEAN_AND_MEAN // Tell the compiler don't bring everything from Windows library in, only those that neccesary
#include <Windows.h> // Importing Windows library (bring in code from Microsoft)
#include <iostream>
//	include the Direct3D 9 library
#include <d3d9.h>
//	include the D3DX9 library
#include <d3dx9.h>
#include <ctime>
//	include the Direct Input library.
#include <dinput.h>
#include <string>
#include "FrameTimer.h"
#include "AudioManager.h"
#include "GameState.h"
#include "Sprite.h"
#include "Parallax.h"
#include "globals.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionManager.h"
#include "Direction.h"
#include "Player.h"
#include "Bullet.h"
#include "Boss.h"
#include "BabyEnemy.h"
#include "Enemy.h"
#include "Coconut.h"
#include "Line.h"
#include "Font.h"
//	Link dinput8.lib and dxguid.lib to your project
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma warning(disable : 4996)
using namespace std;
//--------------------------------------------------------------------

//	Window handle
HWND g_hWnd = NULL; // actually a pointer, this is important like an actual window handle
//--------------------------------------------------------------------

//	Window's structure
WNDCLASS wndClass; // create a class
MSG msg; // create a message container. data type: MSG
// pointer to the virtual GPU
IDirect3DDevice9* d3dDevice;
int windowHeight = 720;
int windowWidth = 1280;

FrameTimer* gameTimer = new FrameTimer();
int gameFPS = 60;

bool windowed = true;


//sprite stuff
// Pointer to a texture -> pointer to a location in your GPU VRAM

// Pointer to the sprite interface - sprite brush
LPD3DXSPRITE spriteBrush = NULL;

LPD3DXLINE line = NULL;
Line* healthBar[3];
struct tm datetime;
Player* player;
BabyEnemy* enemy;
Boss* boss;
Coconut *coconut;
Bullet* bullet;

D3DXVECTOR2 laser[2];

LPD3DXFONT font;
Font* hpText;
Font* menuText;
Font* pauseText;
RECT textRect;
Font* endText;

// DINPUT STUFF
//	Direct Input object.
LPDIRECTINPUT8 dInput;
//	Direct Input keyboard device.
LPDIRECTINPUTDEVICE8  dInputKeyboardDevice;
//	Direct Input keyboard device.
LPDIRECTINPUTDEVICE8  dInputMouseDevice;
//	Key input buffer
BYTE  diKeys[256];
// This is required to hold the state of the mouse
// This variable holds the current state of the mouse device
DIMOUSESTATE mouseState;

// This variable holds the current X position of the sprite
LONG currentXpos = 0;
// This variable holds the current Y position of the sprite
LONG currentYpos = 0;

string mousePositionTxt = "";

//audio stuff
AudioManager* audioManager = new AudioManager();


Parallax* bg[4];
Parallax* menuBg[3];
Sprite* title;
Sprite* pauseScreen;
Sprite* endScreen;
Sprite* endScreens[2];

CollisionManager* collisionManager = new CollisionManager();
GameState currentState = MENU;

void CreateMyWindow();
void CleanupWindow();
bool CreateDirectX();
void CleanUpDirectX();
void CreateObjects();
void CleanUpObjects();
void CreateSprite();
void CleanUpSprite();
void CreateMyFont();
void CleanUpFont();
void CreateLine();
void CleanUpLine();
void CreateDirectInput();
void CleanUpDirectInput();
void GetInput();
void Update();
bool WindowIsRunning();
void ResetGame();
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void Render();

void StartGame() {
	CreateMyWindow();
	CreateDirectX();
	CreateDirectInput();
	CreateObjects();
	CreateSprite();
	CreateMyFont();
	CreateLine();
	audioManager->InitializeAudio();
	audioManager->LoadSounds();
	audioManager->PlaySoundtrack();
	gameTimer->Init(gameFPS);
}
void EndGame() {
	//	Release and clean up everything
	CleanUpLine();
	CleanUpFont();
	CleanUpObjects();
	CleanUpSprite();
	CleanUpDirectInput();
	CleanUpDirectX();
	CleanupWindow();
}
//	use int main if you want to have a console to print out message
//int main()

//	use WinMain if you don't want the console

// windows main() function
int main(HINSTANCE hInstance,// ID number (come from OS)
	HINSTANCE hPrevInstance, //ID number of parent (obsolete, can ignore) 
	LPSTR lpCmdLine, // command line parameter, pass an argument before the program run (important for devs, not for players)
	int nShowCmd) // tell windows what style (not important at all)
{
	StartGame();
	while (WindowIsRunning())
	 {
		//game - > getInput()
		GetInput();
		Update();
		Render();
		audioManager->UpdateSound();
	}

	EndGame();
	
	return 0;
}
//	Window Procedure, for event handling
											// msg type  // what message 
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		//	The message is post when we destroy the window.
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'F':
			windowed = !windowed;
			EndGame();
			StartGame();
			break;
		case VK_ESCAPE:
			if (currentState == PLAYING) {
				currentState = PAUSED;
				audioManager->Pause();
			}
			else if (currentState == PAUSED) {
				currentState = PLAYING;
			}
			else if (currentState == MENU) {
				PostQuitMessage(0);
			}
			break;
		case VK_RETURN:
			if (currentState == MENU) {
				currentState = PLAYING;
				audioManager->Unpause();
			}
			else if (currentState == GAMEEND) {
				currentState = MENU;
				ResetGame();
			}
			else if (currentState == PAUSED) {
				currentState = MENU;
				audioManager->Pause();
				ResetGame();
			}
			break;
		}
		/* 
			Write your code here...
		*/

		//	Default handling for other messages.
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
//--------------------------------------------------------------------
bool WindowIsRunning() {
	/*
			Step 3
			Handling window messages
			NOTE! There are several ways of writing the message loop.
			You have to based on which kind of application your are writing.
		*/
		/*
			The if- version process one message per one iteration loop
			The while- version will clear the message queue before dealing with your own code.

			Another function is GetMessage.
			This function is not suitable for game, because it will block your program until it recieves a message.
			your code will only executed when you have messages, otherwies your pogram will be waiting... (similar to cin)
			Suitable for event based program, such as bussiness app.
		*/
		//	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		//	Receive a quit message
		if (msg.message == WM_QUIT) return false;
		//	Translate the message 
		TranslateMessage(&msg);
		//	Send message to your window procedure
		DispatchMessage(&msg);
	}
	return true;
}


void Render() {

	//	Clear the back buffer.                 clear to white color
	d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(243, 243, 243), 1.0f, 0);

	//	Begin the scene - Unlock the back buffer
	d3dDevice->BeginScene();

	if (currentState == MENU) {
		
		spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);
		for (int i = 2; i >= 0;i--) {
			menuBg[i]->Render();
			menuBg[i]->Move();
		}
		title->Render();
		menuText->Render();
		spriteBrush->End();
	}
	else if (currentState == PLAYING || currentState == PAUSED || currentState == GAMEEND) {
		//	Specify alpha blend will ensure that the sprite will render the background with alpha.
		spriteBrush->Begin(D3DXSPRITE_ALPHABLEND);
		//	Drawing.
		//	Clear and begin scene


		//	Sprite rendering. Study the documentation.
		for (int i = 3; i >= 0;i--) {
			bg[i]->Render();
		}

		player->Render();
		boss->Render();
		hpText->Render();
		if (currentState == PAUSED) {
			pauseScreen->Render();
			pauseText->Render();    // "PAUSED - press ESC to resume"
		}
		else if (currentState == GAMEEND) {
			endScreen->Render();
			endText->Render();
		}
		//	End sprite drawing
		spriteBrush->End();
		for (int i = 2; i >= 0; i--) {
			healthBar[i]->Render();
		}
	}
	//	End and present scene

	//	End the scene - lock the back buffer
	d3dDevice->EndScene();

	//	Present the back buffer to screen
	d3dDevice->Present(NULL, NULL, NULL, NULL);

}
void ResetGame() {
	player->Reset();
	boss->Reset();
	enemy->Reset();
}
void FrameStart() {
	player->ResetForce();
}
void FrameEnd() {
	for (int i = 0; i < 4; i++) {
		bg[i]->Move();
	}
	player->CalculateAnimation();
	enemy->CalculateAnimation();
	coconut->CalculateAnimation();
	boss->CalculateAnimation();
	if (collisionManager->CheckCollision(player, boss)) {
		player->TakeDamage(1);
	}
	list<Bullet*> toRemove;
	for (list<Bullet*>::iterator coconut = enemy->gun.begin(); coconut != enemy->gun.end(); ++coconut) {
		for (list<Bullet*>::iterator bullet = player->gun.begin(); bullet != player->gun.end(); ++bullet) {
			if (collisionManager->CheckCollision(*coconut, *bullet)) {
				collisionManager->knockback(*coconut, *bullet);
				toRemove.push_back(*bullet);
			}
		}
		if (collisionManager->CheckCollision(player, *coconut)) {
			collisionManager->knockback(player, *coconut);
			player->TakeDamage(2);
		}
	}
	for (list<Bullet*>::iterator baby = boss->gun.begin(); baby != boss->gun.end(); ++baby) {
		for (list<Bullet*>::iterator coconut = static_cast<BabyEnemy*>(*baby)->gun.begin(); coconut != static_cast<BabyEnemy*>(*baby)->gun.end(); ++coconut) {
			for (list<Bullet*>::iterator bullet = player->gun.begin(); bullet != player->gun.end(); ++bullet) {
				if (collisionManager->CheckCollision(*coconut, *bullet)) {
					collisionManager->knockback(*coconut, *bullet);
					toRemove.push_back(*bullet);
				}
			}
			if (collisionManager->CheckCollision(player, *coconut)) {
				collisionManager->knockback(player, *coconut);
				player->TakeDamage(1);
			}
		}
	}
	for (list<Bullet*>::iterator bullet = player->gun.begin(); bullet != player->gun.end(); ++bullet) {
		if (collisionManager->CheckCollision(boss, *bullet)) {
			boss->TakeDamage(5);
			toRemove.push_back(*bullet);
		}
		for (list<Bullet*>::iterator baby = boss->gun.begin(); baby != boss->gun.end(); ++baby) {
			if (collisionManager->CheckCollision(*baby, *bullet)) {
				collisionManager->knockback(*baby, *bullet);
				(*baby)->TakeDamage(1);
				toRemove.push_back(*bullet);
			}
		}
	}
	for (list<Bullet*>::iterator it = toRemove.begin(); it != toRemove.end(); ++it) {
		player->gun.remove(*it);
	}
	toRemove.clear();
	boss->Shoot();
	currentXpos += mouseState.lX;
	currentYpos += mouseState.lY;
	frame++;
	player->Move();
	enemy->Move();
	boss->Move();
	healthBar[0]->lineVertices[1].x = player->GetHp() / player->GetMaxHp() * healthBar[0]->length;
	if (player->GetHp() <= 0 || boss->GetHp() <=0) {
		currentState = GAMEEND;
		endScreen = player->GetHp() <= 0 ? endScreens[1] : endScreens[0];
	}
}
void HandleInput() {
	if (diKeys[DIK_UP] & 0x80)
	{
		player->ChangeDirection(UP);
		cout << "UP" << endl;
	}
	if (diKeys[DIK_DOWN] & 0x80)
	{
		player->ChangeDirection(DOWN);
		cout << "DOWN" << endl;
	}
	if (diKeys[DIK_LEFT] & 0x80)
	{
		player->ChangeDirection(LEFT);
		cout << "LEFT" << endl;
	}
	else if (diKeys[DIK_RIGHT] & 0x80)
	{
		player->ChangeDirection(RIGHT);
		cout << "RIGHT" << endl;
	}
	if (diKeys[DIK_SPACE] & 0x80) {
		player->Shoot();
		if (player->GetPosition().x - windowWidth * 0.5 < 0) {
			audioManager->gunShotPan = -1;
		}
		else {
			audioManager->gunShotPan = 1;
		}
	}
}
int frame = 0;
void Update() {

	for (int i = 0; i < gameTimer->FramesToUpdate() && currentState == PLAYING;i++) {
		FrameStart();
		HandleInput();
		FrameEnd();
		
	}
}
//--------------------------------------------------------------------

double DegToRad(double degree) {
	return double(degree) / 180 * 3.142;
}
void CleanUpDirectX() {
	//	Release the device when exiting. remove it from the heap
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;
}
void CreateObjects()
{
	bullet = new Bullet(
		new Sprite("Assets/bullet.png", 32, 32, 32, 29),
		10, 100,windowWidth+100,windowHeight+100);
	player = new Player(
		new Sprite("Assets/airplane.png",1024, 512,  144, 96, 4, 2, 4),
		50,50, windowWidth * 0.2, windowHeight * 0.4, bullet,10,100);
	coconut = new Coconut(
		new Sprite("Assets/coconut.png", 64, 64, 57, 57),
		1, 3, 100 + 100, 200 + 100);
	enemy = new BabyEnemy(
		new Sprite("Assets/PterosaurSheet2.png", 1024, 256,  112, 112, 8, 2, 9),
		30, 100,15, windowWidth * 0.6, windowHeight * 0.6,coconut, 100, 50);
	boss = new Boss(new Sprite("Assets/PterosaurSheet2.png", 1024, 256, 112, 112, 8, 2, 9),
		100, 40, windowWidth * 0.8, windowHeight * 0.6, enemy, 50, 200);
	boss->Scale(3, 3);
	
}
bool CreateDirectX() {//	Define Direct3D 9 OBJECT. (Build virtual graphic card)
	D3DPRESENT_PARAMETERS d3dPP;
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION); // similiarly to
	// int    *     x     = new       int  (       5       )

	//	Define how the screen presents.
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = windowed;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1; // smooth if more but waste memory
	d3dPP.BackBufferWidth = windowWidth; // must match window size or else picture will stretch
	d3dPP.BackBufferHeight = windowHeight; // must match window size or else picture will stretch
	d3dPP.hDeviceWindow = g_hWnd; // must match window handle


	//	Create a Direct3D 9 device.                                                                                               address of ptr
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice); // The function does not return the device. It only return the result aka SUCCESS or FAILED (Error Code)

	//	To Do: Cout out the message to indicate the failure.
	if (FAILED(hr)) {
		cout << hr << endl;
		return 0; // quit the program because there's no virtual graphic card
	}
	return true;
}

void CreateSprite() {
	menuBg[0] = new Parallax(new Sprite("Assets/sea.png", 2048, 1024, windowWidth, windowHeight), 1);
	menuBg[1] = new Parallax(new Sprite("Assets/cloud.png", 2048, 1024, windowWidth, windowHeight), 0.5);
	menuBg[2] = new Parallax(new Sprite("Assets/horizon.png", 2048, 1024, windowWidth, windowHeight), 0.3);

	bg[0] = new Parallax(new Sprite("Assets/land.png", 2048, 1024,windowWidth, windowHeight) ,1);
	bg[1] = new Parallax(new Sprite("Assets/river.png", 2048, 1024, windowWidth, windowHeight) ,0.5);
	bg[2] = new Parallax(new Sprite("Assets/mountain.png", 2048, 1024,  windowWidth, windowHeight),0.3);
	bg[3] = new Parallax(new Sprite("Assets/sky.png", 2048, 1024, windowWidth, windowHeight),0.1);

	title = new Sprite("Assets/title.png", 2048, 1024, windowWidth, windowHeight);
	pauseScreen = new Sprite("Assets/pausescreen.png", 2048, 1024, windowWidth, windowHeight);
	endScreens[0] = new Sprite("Assets/win.png", 2048, 1024, windowWidth, windowHeight);
	endScreens[1] = new Sprite("Assets/lose.png", 2048, 1024, windowWidth, windowHeight);
	//	Create sprite. Study the documentation. 
	HRESULT hr = D3DXCreateSprite(d3dDevice, &spriteBrush);
	if (FAILED(hr)) {
		cout << "Failed to create sprite interface / brush" << endl;
		// return  some eror message
	}

	if (FAILED(hr)) {
		cout << "Failed to load texture" << endl;
		// return  some eror message
	}
}
void CleanUpObjects() {
	player->CleanUp();
	enemy->CleanUp();
	bullet->CleanUp();
	coconut->CleanUp();
}
void CleanUpSprite() {
	for (int i = 0;i < 2;i++) {
		menuBg[i]->CleanUp();
	}
	for (int i = 0;i < 3;i++) {
		bg[i]->CleanUp();
	}
	title->CleanUp();
	pauseScreen->CleanUp();
	spriteBrush->Release();
	spriteBrush = NULL;
}
void CreateMyFont() {
	hpText = new Font("Hp : ", 25, 0, FW_BOLD, false, "Segoe UI", 15, 40, 10, 80, 255, 0, 0);
	menuText = new Font("---------- Press ENTER to start ----------", 35, 0, FW_BOLD, false, "Segoe UI", 500, 600, 0, windowWidth, 255, 255, 255);
	pauseText = new Font("--------------Game Paused--------------\n\n\n\--------- Press ESC to unpause ---------\n\n---- Press ENTER to return to menu ----", 50, 0, FW_BOLD, false, "Segoe UI", windowHeight*0.3, 600, 0, windowWidth, 255, 255, 255);
	endText = new Font("---- Press ENTER to return to menu ----", 35, 0, FW_BOLD, false, "Segoe UI", 500, 600, 0, windowWidth, 255, 255, 255);;
}
void CleanUpFont() {
	hpText->CleanUp(); 
	menuText->CleanUp();
	pauseText->CleanUp();
	endText->CleanUp();
}

void CreateLine() {
	HRESULT hr = D3DXCreateLine(d3dDevice, &line);
	healthBar[0] = new Line(hpText->rect.right, 30, 400, 30, 255, 0, 0, 10,400);
	healthBar[1] = new Line(hpText->rect.right, 30, 400, 30, 0, 0, 0, 10);
	healthBar[2] = new Line(hpText->rect.right - 10, 30, 410, 30, 64, 64, 64, 20);
}
void CleanUpLine() {
	line->Release();
	line = NULL;
}
void CreateMyWindow() {
	/*
		Step 1
		Define and Register a Window.
	*/

	//	Sset all members in wndClass to 0.
	ZeroMemory(&wndClass,// address to find the class
		sizeof(wndClass));	// fill entire class with 0

	//	Filling wndClass. You are to refer to MSDN for each of the members details.
	//	These are the fundamental structure members to be specify, in order to create your window.
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hInstance = GetModuleHandle(NULL); // get hInstance ID
	wndClass.lpfnWndProc = WindowProcedure; // long pointer to function called WindowProcedure at line 11
	wndClass.lpszClassName = "My Window";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	//	Register the window.
	RegisterClass(&wndClass); // function from windows library

	/*
		Step 2
		Create the Window.
	*/
	//	You are to refer to MSDN for each of the parameters details.
				// create a window and put "My Window's Name" as the name                        width and height
	g_hWnd = CreateWindowEx(0, wndClass.lpszClassName, "Plane vs Pterodactyl", WS_OVERLAPPEDWINDOW, 0, 100, windowWidth, windowHeight, NULL, NULL, GetModuleHandle(NULL), NULL);
	ShowWindow(g_hWnd, 1); // ok now show the window

	//	Some interesting function to try out.
	//ShowCursor(false);
	ZeroMemory(&msg, sizeof(msg)); // set everything in the message 0 
}
void CleanupWindow() {
	//	Free up the memory.
	UnregisterClass(wndClass.lpszClassName, GetModuleHandle(NULL));
}
void CreateDirectInput() {
	//	Create the Direct Input object.
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);

	//	Set the input data format.
	dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	//	Create the Direct Input object.
	hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);
	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);

	//	Set the input data format.
	dInputMouseDevice->SetDataFormat(&c_dfDIMouse);

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	//	Acquire the device.
	dInputMouseDevice->Acquire();
}
void CleanUpDirectInput() {
	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;
	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;
}

void GetInput() {
	//	Acquire the device.
	dInputKeyboardDevice->Acquire();
	//	Get immediate Keyboard Data.
	dInputKeyboardDevice->GetDeviceState(256, diKeys);
	//	Acquire the device.
	dInputMouseDevice->Acquire();
	dInputMouseDevice->GetDeviceState(sizeof(mouseState), (LPVOID)&mouseState);
}
