#pragma once

#include "ModDefs.h"
#include "ModObject.h"
#include "ModList.h"

typedef struct GameData {
	long sunAmt;						//	how much sun the player has
	int currentPlant;					//	the current plant the player can buy
	float timeDelta;					//	time since last frame
	sfVector2i mousepos;				//	current frame's mouse position
	unsigned char primaryDown;			//	is primary action activated
	unsigned char primaryReleased;		//	is primary action released
	unsigned char secondaryDown;		//	is secondary action activated
	unsigned char secondaryReleased;	//	is secondary action released
	unsigned char leftDown;				//	is left action activated
	unsigned char leftReleased;			//	is left action released
	unsigned char rightDown;			//	is right action activated
	unsigned char rightReleased;		//	is right action released
	ModObject* plantGrid[MOD_GRID_ROWS][MOD_GRID_COLS];	//	grid of plants
} GameData;

GameData gameData;

ModList* gameObjects;
ModList* uiObjects;

/// <summary>
/// Initializes game by binding common actions
/// </summary>
void ModGameInit();
void ModGameUpdate();
void ModGameCleanup();