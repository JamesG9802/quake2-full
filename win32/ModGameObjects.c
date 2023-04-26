#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void ProjectileThink(ModObject* object) {
	if (object && object->data && ((ModList*)(object->data))->elements[0])
	{
		double speed = *(double*)(((ModList*)(object->data))->elements[1]);
		sfVector2f newPosition;
		newPosition.x = object->position.x + speed * gameData.timeDelta * MOD_GRID_WIDTH;
		newPosition.y = object->position.y;
		ModObject_SetPosition(object, newPosition);
		//	Unoptimized collision detection
		for (int i = 0; i < gameObjects->length; i++)
		{
			//	Is a zombie
			if (((ModObject*)(gameObjects->elements[i]))->className &&
				strcmp(((ModObject*)(gameObjects->elements[i]))->className, MOD_CLASS_ZOMBIE) == 0)
			{
				ModObject* zombie = (ModObject*)(gameObjects->elements[i]);
				//	is in bounds
				if (object->position.x >= zombie->position.x && 
					object->position.x <= zombie->position.x + MOD_ZOMBIE_PNG_WIDTH &&
					object->position.y >= zombie->position.y &&
					object->position.y <= zombie->position.y + MOD_ZOMBIE_PNG_HEIGHT)
				{
					double damage = *((double*)(((ModList*)(object->data))->elements[0]));
					DamageZombie(zombie, damage);
					ModObject_Destroy(object);
					return;
				}
			}
		}
	}
}
void ProjectileDestroy(ModObject* object) {
	for (int i = 0; i < ((ModList*)object->data)->length; i++)
	{
		free(((ModList*)object->data)->elements[i]);
	}
	ModList_Destroy(object->data);
}
ModObject* CreateProjectile(double damage, double speed, const char* imagePath)
{
	
	ModObject* object = ModObject_Create(imagePath);
	
	sfVector2f scale;
	scale.x = (float)MOD_PROJECTILE_PNG_WIDTH / MOD_PROJECTILE0_PNG_WIDTH;
	scale.y = (float)MOD_PROJECTILE_PNG_HEIGHT/ MOD_PROJECTILE0_PNG_WIDTH;
	ModObject_Resize(object, scale);
	
	object->data = ModList_Create();

	double* damageParameter = malloc(sizeof(double));
	double* speedParameter = malloc(sizeof(double));

	*damageParameter = damage;
	*speedParameter = speed;

	ModList_Append(object->data, damageParameter);
	ModList_Append(object->data, speedParameter);

	object->Think = ProjectileThink;
	object->Destroy = ProjectileDestroy;
	
	return object;
}
void GridThink(ModObject* object) {
	if (!object) return;

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
		ModObject* plant = CreatePlant(MOD_PEASHOOTER);
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
}
