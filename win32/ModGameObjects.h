#pragma once

#include "SFML/Graphics.h"
#include "SFML/Graphics/RectangleShape.h"
#include "SFML/Graphics/Color.h"
#include "SFML/System/Vector2.h"

#include "ModGame.h"
#include "ModDefs.h"
#include "ModSysVars.h"
#include "ModObject.h"

/*	Utility Class containing common game object related functions*/


/// <summary>
/// Creates a plant given its grid coordinates
/// </summary>
/// <returns></returns>
ModObject* CreatePlant(int x, int y)
{
	ModObject* object = ModObject_Create(MOD_SUNFLOWER_PNG);
	sfVector2f scale;
	scale.x = MOD_GRID_XPOS + MOD_GRID_WIDTH * x;
	scale.y = MOD_GRID_YPOS + MOD_GRID_HEIGHT * y + (MOD_GRID_HEIGHT - MOD_GRID_YPOS) / 2;
	ModObject_SetPosition(object, scale);
	scale.x = (float)MOD_GRID_WIDTH / MOD_PLANT_PNG_WIDTH;
	scale.y = (float)MOD_GRID_WIDTH / MOD_PLANT_PNG_WIDTH;
	ModObject_Resize(object, scale);
	ModList_Append(gameObjects, object);
}


/// <summary>
/// Think function for the grid squares
/// </summary>
/// <param name="object"></param>
void GridThink(ModObject* object) {
	sfRectangleShape* rect = sfRectangleShape_create();

	if (!object) return;

	/*	Doesn't work because render immediately clears
	sfRectangleShape_setFillColor(rect, sfRed);
	sfRectangleShape_setPosition(rect, object->position);
	sfRenderWindow_drawRectangleShape(window, rect, NULL);
	*/
	sfVector2i mousepos = sfMouse_getPositionRenderWindow(window);
	
	/*	Outside the bounds	*/
	if (mousepos.x < object->position.x || mousepos.x > object->position.x + MOD_GRID_WIDTH ||
		mousepos.y < object->position.y || mousepos.y > object->position.y + MOD_GRID_HEIGHT)
	{
		object->shouldDraw = 0;
		return;
	}
	object->shouldDraw = 1;
	if (gameData.primaryReleased)
	{
		int x = (mousepos.x - MOD_GRID_XPOS) / MOD_GRID_WIDTH;
		int y = (mousepos.y - MOD_GRID_YPOS) / MOD_GRID_HEIGHT;

		printf("%d %d\n", x, y);
		CreatePlant(x, y);
	}
}
void GameThink(ModObject* object) {
	static float time = 0;
	time += timeDelta;
	if (time >= 1)
	{
		time--;
	}
}
