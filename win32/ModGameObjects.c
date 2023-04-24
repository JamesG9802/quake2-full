#include <stdio.h>

#include "SFML/Graphics.h"
#include "SFML/Graphics/RectangleShape.h"
#include "SFML/Graphics/Color.h"
#include "SFML/System/Vector2.h"

#include "ModGame.h"
#include "ModDefs.h"
#include "ModSysVars.h"
#include "ModObject.h"
#include "ModPlant.h"
#include "ModZombie.h"

void PlaceZombie(ModObject* object, int x, int y)
{
	sfVector2f position;
	position.x = MOD_GRID_XPOS + MOD_GRID_WIDTH * x;
	position.y = MOD_GRID_YPOS + MOD_GRID_HEIGHT * y + (MOD_GRID_HEIGHT - MOD_GRID_YPOS) / 2;
	ModObject_SetPosition(object, position);
	sfVector2f scale;
//	scale.x = (float)MOD_GRID_WIDTH / MOD_ZOMBIE_PNG_WIDTH;
//	scale.y = (float)MOD_GRID_WIDTH / MOD_ZOMBIE_PNG_HEIGHT;
//	ModObject_Resize(object, scale);
	ModList_Append(gameObjects, object);
}

void PlacePlant(ModObject* object, int x, int y)
{
	//	If grid square is already occupied, do nothing
	if (gameData.plantGrid[y][x])
		return NULL;
	sfVector2f position;
	position.x = MOD_GRID_XPOS + MOD_GRID_WIDTH * x;
	position.y = MOD_GRID_YPOS + MOD_GRID_HEIGHT * y + (MOD_GRID_HEIGHT - MOD_GRID_YPOS) / 2;
	ModObject_SetPosition(object, position);
	sfVector2f scale;
	scale.x = (float)MOD_GRID_WIDTH / MOD_PLANT_PNG_WIDTH;
	scale.y = (float)MOD_GRID_WIDTH / MOD_PLANT_PNG_WIDTH;
	ModObject_Resize(object, scale);
	ModList_Append(gameObjects, object);
	gameData.plantGrid[y][x] = object;
}

void SunThink(ModObject* object) {
	sfVector2i mousepos = gameData.mousepos;
	/*	Outside the bounds	*/
	if (mousepos.x < object->position.x || mousepos.x > object->position.x + MOD_SUN_WIDTH ||
		mousepos.y < object->position.y || mousepos.y > object->position.y + MOD_SUN_HEIGHT)
	{
		return;
	}
	//	Otherwise collect sun
	gameData.sunAmt += MOD_GAME_SUNVALUE;
	ModList_RemoveC(gameObjects, object);
	ModObject_Destroy(object);
	return;
}
ModObject* CreateSun()
{
	ModObject* object = ModObject_Create(MOD_SUN_PNG);

	sfVector2f scale;
	scale.x = (float)MOD_SUN_WIDTH / MOD_SUN_PNG_WIDTH;
	scale.y = (float)MOD_SUN_WIDTH / MOD_SUN_PNG_WIDTH;
	ModObject_Resize(object, scale);
	object->Think = SunThink;
	return object;
}
void GridThink(ModObject* object) {
	sfRectangleShape* rect = sfRectangleShape_create();

	if (!object) return;

	/*	Doesn't work because render immediately clears
	sfRectangleShape_setFillColor(rect, sfRed);
	sfRectangleShape_setPosition(rect, object->position);
	sfRenderWindow_drawRectangleShape(window, rect, NULL);
	*/
	sfVector2i mousepos = gameData.mousepos;

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
		if (gameData.plantGrid[y][x])
			return;
		printf("%d %d\n", x, y);
		ModObject* plant = CreatePlant(MOD_SUNFLOWER);
		PlacePlant(plant, x, y);
	}
	if (gameData.secondaryReleased)
	{
		int x = (mousepos.x - MOD_GRID_XPOS) / MOD_GRID_WIDTH;
		int y = (mousepos.y - MOD_GRID_YPOS) / MOD_GRID_HEIGHT;
		printf("Zombie %d %d\n", x, y);
		ModObject* zombie = CreateZombie(MOD_ZOMBIE_REGULAR);
		if (zombie == NULL)
			printf("NULL");
		PlaceZombie(zombie, x, y);
	}
}
void GameThink(ModObject* object) {
	static float time = 0;
	time += gameData.timeDelta;
	if (time >= 1)
	{
		time--;
	}
}
