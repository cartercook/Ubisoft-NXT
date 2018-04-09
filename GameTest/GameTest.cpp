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
#include "app\main.h"
#include "CEntity.h"
#include "ball.h"
#include "editor.h"
#include "flipper.h"

CTable level;
Ball ball = Ball(550, 600, 25);
Flipper *leftFlipper = new Flipper(WINDOW_WIDTH/2 - 100, 130, false);
Flipper *rightFlipper = new Flipper(WINDOW_WIDTH/2 + 100, 130, true);

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
	leftFlipper->Update(deltaTime);
	rightFlipper->Update(deltaTime);

	ball.Collide(level, deltaTime);
	ball.Collide(leftFlipper, leftFlipper->table, deltaTime);
	ball.Collide(rightFlipper, rightFlipper->table, deltaTime);
}

//------------------------------------------------------------------------
// Add your display calls here (DrawLine or Print) 
// See App.h 
//------------------------------------------------------------------------
void Render()
{
	ball.Render();
	leftFlipper->Render();
	rightFlipper->Render();
	level.Render();
}

//------------------------------------------------------------------------
// Add your shutdown code here. Called when the APP_QUIT_KEY is pressed.
// Just before the app exits.
//------------------------------------------------------------------------
void Shutdown()
{
	delete leftFlipper;
	delete rightFlipper;
}
