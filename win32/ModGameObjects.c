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
	sfSprite_setColor(object->modsprite->sprite,sfColor_fromRGBA(255, 255, 255, 200));
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

					ModList_RemoveC(gameObjects, object);
					ModObject_Destroy(object);
					return;
				}
			}
		}
		//	Out of window
		if (newPosition.x > MOD_WINDOW_WIDTH)
		{
			ModList_RemoveC(gameObjects, object);
			ModObject_Destroy(object);
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

	object->className = malloc(sizeof(char) * (strlen(MOD_CLASS_PROJECTILE) + 1));
	strcpy(object->className, MOD_CLASS_PROJECTILE);

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
ModObject* tryBuyPlant(int plant) {
	int cost = 0;
	switch (plant)
	{
	default:
	case MOD_SUNFLOWER:	cost = MOD_SUNFLOWER_COST; break;
	case MOD_PEASHOOTER:	cost = MOD_PEASHOOTER_COST; break;
	case MOD_WALLNUT:	cost = MOD_WALLNUT_COST; break;
	case MOD_CHERRYBOMB:	cost = MOD_CHERRYBOMB_COST; break;
	case MOD_JALEPENO:	cost = MOD_JALEPENO_COST; break;
	case MOD_EXPLODENUT:	cost = MOD_EXPLODENUT_COST; break;
	case MOD_REPEATER:	cost = MOD_REPEATER_COST; break;
	case MOD_TORCHWOOD:	cost = MOD_TORCHWOOD_COST; break;
	case MOD_MOUSESHOOTER:	cost = MOD_MOUSESHOOTER_COST; break;
	case MOD_CHOMPER:	cost = MOD_CHOMPER_COST; break;
	}
	if (cost <= gameData.sunAmt)
	{
		gameData.sunAmt -= cost;
		return CreatePlant(plant);
	}
	return NULL;
}
void LawnmowerThink(ModObject* object) {
	sfVector2f position = object->position;
	position.x += MOD_PROJECTILE_SPEED_NORMAL * MOD_GRID_WIDTH * gameData.timeDelta;
	ModObject_SetPosition(object, position);

	float x = object->position.x;
	float y = object->position.y;
	for (int i = 0; i < gameObjects->length; i++)
	{
		if (((ModObject*)(gameObjects->elements[i]))->className &&
			strcmp(((ModObject*)(gameObjects->elements[i]))->className, MOD_CLASS_ZOMBIE) == 0)
		{
			float zx = ((ModObject*)(gameObjects->elements[i]))->position.x;
			float zy = ((ModObject*)(gameObjects->elements[i]))->position.y;
			if (zx >= x  && zx <= x + MOD_PLANT_PNG_WIDTH &&
				zy >= y && zy <= y + MOD_PLANT_PNG_HEIGHT)
			{
				DamageZombie(gameObjects->elements[i], MOD_DAMAGE_INSTANTKILL);
				break;
			}
		}
	}

	if (position.x > MOD_WINDOW_WIDTH) {
		ModList_RemoveC(gameObjects, object);
		ModObject_Destroy(object);
	}
}
ModObject* CreateLawnmower() {
	ModObject* object = ModObject_Create(MOD_CONSUMABLE_LAWNMOWER_PNG);
	sfVector2f scale;
	scale.x = (float)MOD_GRID_WIDTH / MOD_CONSUMABLE_PNG_WIDTH;
	scale.y = (float)MOD_GRID_WIDTH / MOD_CONSUMABLE_PNG_HEIGHT;
	ModObject_Resize(object, scale);
	object->Think = LawnmowerThink;
	object->shouldDraw = 1;
	return object;
}
void GridThink(ModObject* object) {
	static int zombieIndex = 0;
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
		ModObject* plant = tryBuyPlant(gameData.currentPlant);
		if (plant)
			PlacePlant(plant, x, y);
	}
	if (gameData.secondaryReleased)	//	consumable resolution for SHOVEL and LAWNMOWER

	{
		int x = (mousepos.x - MOD_GRID_XPOS) / MOD_GRID_WIDTH;
		int y = (mousepos.y - MOD_GRID_YPOS) / MOD_GRID_HEIGHT;
		switch (gameData.currentConsumable)
		{
		default: break;
		case MOD_CONSUMABLE_SHOVEL:
			
			if (!gameData.plantGrid[y][x])
				break;
			ModList_RemoveC(gameObjects, gameData.plantGrid[y][x]);
			ModObject_Destroy(gameData.plantGrid[y][x]);
			gameData.plantGrid[y][x] = NULL;
			gameData.currentConsumable = MOD_CONSUMABLE_NONE;
			break;
		case MOD_CONSUMABLE_LAWNMOWER:
			;ModObject* lawnmower = CreateLawnmower();
			sfVector2f position;
			position.x = MOD_GRID_XPOS;
			position.y = MOD_GRID_YPOS + MOD_GRID_HEIGHT * y + (MOD_GRID_HEIGHT - MOD_GRID_YPOS) / 2;
			ModObject_SetPosition(lawnmower, position);
			ModList_Append(gameObjects, lawnmower);
			gameData.currentConsumable = MOD_CONSUMABLE_NONE;
			break;
		}
	}
	if (gameData.debugReleased)
	{
		int x = (mousepos.x - MOD_GRID_XPOS) / MOD_GRID_WIDTH;
		int y = (mousepos.y - MOD_GRID_YPOS) / MOD_GRID_HEIGHT;
		printf("Zombie %d %d\n", x, y);
		ModObject* zombie = CreateZombie(zombieIndex);
		if (zombie == NULL)
			printf("NULL");
		PlaceZombie(zombie, x, y);
		zombieIndex++;
		if (zombieIndex > MOD_ZOMBIE_FOOTBALL)
			zombieIndex = MOD_ZOMBIE_REGULAR;
	}
}
void GameThink(ModObject* object) {
	static double time = 0;
	static double difficulty = 0;

	time += gameData.timeDelta;
	difficulty += .5 * gameData.timeDelta;
	int xOffset = 0;
	if ((int)(time) % 8 == 0)
	{
		time++;
		for (double initDifficulty = difficulty; initDifficulty > 0; initDifficulty--)
		{
			int x = MOD_GRID_COLS + 1 + xOffset;
			int y = (int)((((float)rand() / (float)(RAND_MAX / MOD_GRID_ROWS))));
			

			ModObject* zombie = NULL;
			if ((float)rand() / (float)RAND_MAX >.5 && initDifficulty > 6)
			{
				zombie = CreateZombie(MOD_ZOMBIE_REGULAR);
				initDifficulty -= 6;
			}
			else if ((float)rand() / (float)RAND_MAX > .5 && initDifficulty > 12)
			{
				zombie = CreateZombie(MOD_ZOMBIE_FLAG);
				initDifficulty -= 12;
			}
			else if ((float)rand() / (float)RAND_MAX > .5 && initDifficulty > 18)
			{
				zombie = CreateZombie(MOD_ZOMBIE_CONE);
				initDifficulty -= 12;
			}
			else if ((float)rand() / (float)RAND_MAX > .5 && initDifficulty > 24)
			{
				zombie = CreateZombie(MOD_ZOMBIE_BUCKET);
				initDifficulty -= 24;
			}
			else if ((float)rand() / (float)RAND_MAX > .5 && initDifficulty > 32)
			{
				zombie = CreateZombie(MOD_ZOMBIE_FOOTBALL);
				initDifficulty -= 32;
			}
			if (zombie)
			{
				printf("Zombie %d %d\n", x, y);
				PlaceZombie(zombie, x, y);
			}
			xOffset += 2;
		}
		sfVector2f pos;
		pos.x = (float)rand() / (float)RAND_MAX * MOD_WINDOW_WIDTH * .9 + 10;
		pos.y = (float)rand() / (float)RAND_MAX * MOD_WINDOW_HEIGHT * .9 + 10;
		ModObject* sun = CreateSun();
		ModObject_SetPosition(sun, pos);
		ModList_Append(gameObjects, sun);
	}

	if (gameData.debugReleased) {	//	debug add powerup
		gameData.currentConsumable++;
		if (gameData.currentConsumable > MOD_HIGHEST_CONSUMABLE_INDEX)
			gameData.currentConsumable = MOD_LOWEST_CONSUMABLE_INDEX;
		printf("Current consumable == %d\n", gameData.currentConsumable);
	}
	if (gameData.secondaryReleased) {
		//	Consumable Resolution for SUN, PUSH ZOMBIE, & FREEZE ZOMBIE
		switch (gameData.currentConsumable)
		{
		default: break;
		case MOD_CONSUMABLE_SUN:
			for (int i = 0;i < 4; i++) {
				sfVector2f pos;
				pos.x = (float)rand() / (float)RAND_MAX * MOD_WINDOW_WIDTH * .9 + 10;
				pos.y = (float)rand() / (float)RAND_MAX * MOD_WINDOW_HEIGHT * .9 + 10;
				ModObject* sun = CreateSun();
				ModObject_SetPosition(sun, pos);
				ModList_Append(gameObjects, sun);
			}
			gameData.currentConsumable = MOD_CONSUMABLE_NONE;
			break;
		case MOD_CONSUMABLE_PUSHZOMBIE:
			for (int i = 0; i < gameObjects->length; i++)
			{
				if (((ModObject*)(gameObjects->elements[i]))->className &&
					strcmp(((ModObject*)(gameObjects->elements[i]))->className, MOD_CLASS_ZOMBIE) == 0)
				{
					sfVector2f position;
					position.x = ((ModObject*)(gameObjects->elements[i]))->position.x;
					position.y = ((ModObject*)(gameObjects->elements[i]))->position.y;
					position.x += 300;
					ModObject_SetPosition(((ModObject*)(gameObjects->elements[i])), position);
				}
			}
			gameData.currentConsumable = MOD_CONSUMABLE_NONE;
			break;
		case MOD_CONSUMABLE_FREEZEZOMBIE:
			for (int i = 0; i < gameObjects->length; i++)
			{
				ModObject* zombie = gameObjects->elements[i];
				if (((ModObject*)(gameObjects->elements[i]))->className &&
					strcmp(((ModObject*)(gameObjects->elements[i]))->className, MOD_CLASS_ZOMBIE) == 0)
				{
					*((double*)((ModList*)(zombie->data))->elements[3]) = MOD_ZOMBIE_STATUS_FREEZE;
				}
			}
			gameData.currentConsumable = MOD_CONSUMABLE_NONE;
			break;
		}
	}
}
