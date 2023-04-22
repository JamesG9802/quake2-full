#pragma once

#include "ModObject.h"
#include "ModList.h"

typedef struct GameData {
	long sunAmt;		//	how much sun the player has
	unsigned char primaryDown;			//	is primary action activated
	unsigned char primaryReleased;		//	is primary action released
	unsigned char secondaryDown;		//	is secondary action activated
	unsigned char secondaryReleased;	//	is secondary action released
} GameData;

GameData gameData;

ModList* gameObjects;
ModList* uiObjects;

float timeDelta;	//	time since last frame

/// <summary>
/// Initializes game by binding common actions
/// </summary>
void ModGameInit();
void ModGameUpdate();
void ModGameCleanup();