#include <stdlib.h>
#include <stdio.h>

#include <SFML/Window.h>
#include <SFML/System/Vector2.h>

#include "ModDefs.h"
#include "ModGame.h"
#include "ModSysVars.h"
#include "ModObject.h"
#include "ModList.h"
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

	/*	Draw Background	*/
	gameObjects = ModList_Create();

	ModObject* background = ModObject_Create("pics/lawn.png");
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
}
void ModGameUpdate()
{
	sfVector2i mousepos = sfMouse_getPositionRenderWindow(window);
	//printf("%d %d", mousepos.x, mousepos.y);
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
}