#include <stdlib.h>
#include <stdio.h>

#include <SFML/Window.h>
#include <SFML/System/Vector2.h>

#include "ModList.h"
#include "ModPriorityQueue.h"

#include "ModDefs.h"
#include "ModSysVars.h"

#include "ModGame.h"
#include "ModObject.h"
#include "ModObjectUI.h"

#include "ModGameObjects.h"

extern void (*Primary_Action)(void);
extern void (*Secondary_Action)(void);

extern GameData gameData;
extern ModList* gameObjects = NULL;
extern ModList* uiObjects = NULL;

sfClock* clock = NULL;

void ModGameInit()
{
	/*	Initialize Global Variables	*/
	gameData.sunAmt = MOD_GAME_INITSUN;
	gameData.currentPlant = MOD_SUNFLOWER;
	for (int y = 0; y < MOD_GRID_ROWS; y++)
		for (int x = 0; x < MOD_GRID_COLS; x++)
			gameData.plantGrid[y][x] = NULL;

	gameObjects = ModList_Create();
	uiObjects = ModPriorityQueue_Create();
	clock = sfClock_create();

	/*	Add Game Manager	*/
	ModObject* manager = ModObject_CreateNoSprite();
	manager->Think = GameThink;
	ModList_Append(gameObjects, manager);

	/*	Add Background	*/
	ModObject* background = ModObject_Create(MOD_BACKGROUND_PNG);
	sfVector2f position;
	position.x = MOD_BACKGROUND_XOFFSET;
	position.y = 0;
	ModObject_SetPosition(background, position);
	ModList_Append(gameObjects, background);

	/*	Add Grid Squares	*/
	for (int y = 0; y < MOD_GRID_ROWS; y++)
	{
		for (int x = 0; x < MOD_GRID_COLS; x++)
		{
			ModObject* gridsquare = ModObject_Create(MOD_GRIDGLOW_PNG);
			sfVector2f position;
			position.x = MOD_GRID_XPOS + MOD_GRID_WIDTH * x;
			position.y = MOD_GRID_YPOS + MOD_GRID_HEIGHT * y;
			ModObject_SetPosition(gridsquare, position);
			position.x = (float)MOD_GRID_WIDTH / MOD_GRIDGLOW_PNG_HEIGHT;
			position.y = (float)MOD_GRID_HEIGHT / MOD_GRIDGLOW_PNG_WIDTH;
			ModObject_Resize(gridsquare, position);
			gridsquare->Think = GridThink;
			gridsquare->shouldDraw = 0;
			ModList_Append(gameObjects, gridsquare);
		}
	}
	/*	Add UI elements	*/
	ModObject* ui = UI_CreateSunCounter();
	ModPriorityQueue_Insert(uiObjects, ui, 10);

	ModObject* plantshop = UI_CreatePlantBuy();
	position.x = MOD_SUNUI_PNG_WIDTH + 10;
	position.y = 0;
	ModObject_SetPosition(plantshop, position);
	ModPriorityQueue_Insert(uiObjects, plantshop, 11);

	ModObject* pausemenu = UI_CreateHelp();
	ModPriorityQueue_Insert(uiObjects, pausemenu, 0);

	ModObject* gamestatus = UI_CreateGameStatus();
	ModPriorityQueue_Insert(uiObjects, gamestatus, 0);
}
/// <summary>
/// UI thinks first, then game objects
/// </summary>
void ModGameUpdate()
{
	if(!gameData.gamePaused)
		gameData.timeDelta = sfTime_asMilliseconds(sfClock_restart(clock)) / 1000.0;
	else	//	consume the delta
		sfTime_asMilliseconds(sfClock_restart(clock)) / 1000.0;
	gameData.mousepos = sfMouse_getPositionRenderWindow(window);
	
	for (int i = 0; i < uiObjects->length; i++)
	{
		if (((ModObject*)(ModPriorityQueue_At(uiObjects, i)))->Think != NULL)
		{
			((ModObject*)(ModPriorityQueue_At(uiObjects, i)))->Think((ModObject*)ModPriorityQueue_At(uiObjects, i));
		}
	}

	if (!gameData.gamePaused)
	for (int i = 0; i < gameObjects->length; i++)
	{
		int currentLength = gameObjects->length;
		if (((ModObject*)gameObjects->elements[i])->Think != NULL)
		{
			((ModObject*)gameObjects->elements[i])->Think(((ModObject*)gameObjects->elements[i]));
		}
		if (currentLength != gameObjects->length)	//	hack solution to if a gameObject destroys itself
			i = i;
	}
}
void ModGameCleanup()
{
	//	Game Data
	/*	Don't actually need to free the grid because all grid objects are in gameobjects
	for (int y = 0; y < MOD_GRID_ROWS; y++)
		for (int x = 0; x < MOD_GRID_COLS; x++)
		{
			if(gameData.plantGrid[y][x])
				ModObject_Destroy(gameData.plantGrid[y][x]);
		}
	*/
	if (gameObjects)
	{
		for (int i = 0; i < gameObjects->length; i++)
		{
			if (gameObjects->elements[i])
				ModObject_Destroy(gameObjects->elements[i]);
		}
		ModList_Destroy(gameObjects);
	}
	if (uiObjects)
	{
		for (int i = 0; i < uiObjects->length; i++)
		{
			if (ModPriorityQueue_At(uiObjects, i))
				ModObject_Destroy(ModPriorityQueue_At(uiObjects, i));
		}
		ModPriorityQueue_Destroy(uiObjects);
	}
	if(clock)
		sfClock_destroy(clock);
}