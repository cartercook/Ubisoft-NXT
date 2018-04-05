//------------------------------------------------------------------------
// GameTest.cpp
//------------------------------------------------------------------------
#include "stdafx.h"
//------------------------------------------------------------------------
#include <windows.h> 
#include <math.h> 
#include <iostream>
//------------------------------------------------------------------------
#include "app\app.h"
#include "CEntity.h"
#include "ball.h"
#include "Editor.h"
CTable level;
Ball ball = Ball(300, 700, 25);

//------------------------------------------------------------------------
// Called before first update. Do any initial setup here.
//------------------------------------------------------------------------
void Init()
{
	level = Editor::Load("table.txt");
}

//------------------------------------------------------------------------
// Update your simulation here. deltaTime is the elapsed time since the last update in ms.
// This will be called at no greater frequency than the value of APP_MAX_FRAME_RATE
//------------------------------------------------------------------------
void Update(float deltaTime)
{
	ball.Update(deltaTime);
	ball.Collide(level);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	ball.Render();
	level.Render();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
}