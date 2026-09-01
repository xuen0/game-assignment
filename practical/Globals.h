#pragma once
#include <d3dx9.h>
#include "AudioManager.h"
#include "GameState.h"
extern LPD3DXSPRITE spriteBrush;
extern IDirect3DDevice9* d3dDevice;
extern int windowHeight;
extern int windowWidth;
extern int frame;
extern AudioManager* audioManager;
extern double DegToRad(double degree);
extern LPD3DXLINE line;
extern LPD3DXFONT font;
extern GameState currentState;