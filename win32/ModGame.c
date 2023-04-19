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

extern ModList* gameObjects = NULL;
void Game_Primary()
{
	printf("primary action\n");
}
void Game_Secondary()
{
	printf("Secondary action\n");
}

void ModGameInit()
{
	/*	Initialize Input Actions	*/
	Primary_Action = Game_Primary;
	Secondary_Action = Game_Secondary;

	gameObjects = ModList_Create();
	uiObjects = ModPriorityQueue_Create();
	
	ModObject* ui = CreateModUI(MOD_PEASHOOTER_PNG);
	ModPriorityQueue_Insert(uiObjects, ui, 10);

	/*	Draw Background	*/
	
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
			ModObject* gridsquare = ModObject_CreateNoSprite();
			sfVector2f position;
			position.x = MOD_GRID_XPOS + MOD_GRID_WIDTH * x;
			position.y = MOD_GRID_YPOS + MOD_GRID_HEIGHT * y;
			ModObject_SetPosition(gridsquare, position);
			gridsquare->Think = GridThink;
			ModList_Append(gameObjects, gridsquare);
		}
	}
	background = ModObject_Create(MOD_SUNFLOWER_PNG);
	position.x = MOD_GRID_XPOS + MOD_GRID_WIDTH * 5;
	position.y = MOD_GRID_YPOS + MOD_GRID_HEIGHT * 2;
	ModObject_SetPosition(background, position);
	position.x = (float)MOD_GRID_WIDTH / MOD_PLANT_PNG_WIDTH;
	position.y = (float)MOD_GRID_WIDTH / MOD_PLANT_PNG_WIDTH;
	ModObject_Resize(background, position);
	ModList_Append(gameObjects, background);

	background = ModObject_Create(MOD_PEASHOOTER_PNG);
	position.x = MOD_GRID_XPOS + MOD_GRID_WIDTH * 2;
	position.y = MOD_GRID_YPOS + MOD_GRID_HEIGHT * 2;
	ModObject_SetPosition(background, position);
	position.x = (float)MOD_GRID_WIDTH / MOD_PLANT_PNG_WIDTH;
	position.y = (float)MOD_GRID_WIDTH / MOD_PLANT_PNG_WIDTH;
	ModObject_Resize(background, position);
	ModList_Append(gameObjects, background);

	
}
/// <summary>
/// UI thinks first, then game objects
/// </summary>
void ModGameUpdate()
{
	for (int i = 0; i < uiObjects->length; i++)
	{
		if (((ModObject*)(ModPriorityQueue_At(uiObjects, i)))->Think != NULL)
		{
			((ModObject*)(ModPriorityQueue_At(uiObjects, i)))->Think((ModObject*)ModPriorityQueue_At(uiObjects, i));
		}
	}
	for (int i = 0; i < gameObjects->length; i++)
	{
		if (((ModObject*)gameObjects->elements[i])->Think != NULL)
		{
			((ModObject*)gameObjects->elements[i])->Think(((ModObject*)gameObjects->elements[i]));
		}
	}
}
void ModGameCleanup()
{
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
}