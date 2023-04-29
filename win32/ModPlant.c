#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ModDefs.h"
#include "ModGame.h"
#include "ModObject.h"
#include "ModGameObjects.h"
#include "ModPlant.h"
#include "ModZombie.h"

void PlantThink(ModObject* object) {
	int colorSpeed = 1024;
	sfColor color = sfSprite_getColor(object->modsprite->sprite);
	if ((unsigned char)(color.r + colorSpeed * gameData.timeDelta) < color.r)
		color.r = 255;
	else
		color.r += colorSpeed * gameData.timeDelta;
	if ((unsigned char)(color.g + colorSpeed * gameData.timeDelta) < color.g)
		color.g = 255;
	else
		color.g += colorSpeed * gameData.timeDelta;
	if ((unsigned char)(color.b + colorSpeed * gameData.timeDelta) < color.b)
		color.b = 255;
	else
		color.b += colorSpeed * gameData.timeDelta;
	sfSprite_setColor(object->modsprite->sprite, color);

	if (object && object->data && ((ModList*)object->data)->elements[0]) {
		double health = *((double*)((ModList*)object->data)->elements[0]);
		if (health <= 0)
		{
			int x = (object->position.x - MOD_GRID_XPOS) / MOD_GRID_WIDTH;
			int y = (object->position.y - MOD_GRID_YPOS) / MOD_GRID_HEIGHT;
			gameData.plantGrid[y][x] = NULL;
			ModList_RemoveC(gameObjects, object);
			ModObject_Destroy(object);
		}
	}
}
void SunFlowerThink(ModObject* object) {
	if (object && object->data && ((ModList*)(object->data))->elements[1])
	{
		double* time = ((double*)((ModList*)(object->data))->elements[1]);
		*time += gameData.timeDelta;
		PlantThink(object);
		if (!object)
			return;
		if (*time >= MOD_SUNFLOWER_COOLDOWN)
		{
			(*time)-= MOD_SUNFLOWER_COOLDOWN;
			ModObject* sun = CreateSun();
			sfVector2f position = object->position;
			position.x += (((float)rand() / (float)(RAND_MAX / 2)) - 1) * 30;
			position.y += (((float)rand() / (float)(RAND_MAX / 2)) - 1) * 30;
			ModObject_SetPosition(sun, position);
			ModList_Append(gameObjects, sun);
		}
	}
}
void PeashooterThink(ModObject* object) {
	if (object && object->data && ((ModList*)(object->data))->elements[1])
	{
		double* time = ((double*)((ModList*)(object->data))->elements[1]);
		*time += gameData.timeDelta;
		PlantThink(object);
		if (!object)
			return;
		if (*time >= MOD_PEASHOOTER_COOLDOWN)
		{
			(*time) -= MOD_PEASHOOTER_COOLDOWN;
			ModObject* projectile = CreateProjectile(MOD_PLANT_DAMAGE_NORMAL, MOD_PROJECTILE_SPEED_NORMAL, MOD_PEA_PNG);
			sfVector2f position = object->position;
			position.x += MOD_GRID_WIDTH;
			position.y -= (MOD_PROJECTILE_PNG_HEIGHT -  MOD_GRID_HEIGHT) / 2.0;
			ModObject_SetPosition(projectile, position);
			ModList_Append(gameObjects, projectile);
			
		}
	}
}
void CherryBombThink(ModObject* object) {
	if (object && object->data && ((ModList*)(object->data))->elements[1])
	{
		double* health = ((double*)((ModList*)object->data)->elements[0]);
		double* time = ((double*)((ModList*)(object->data))->elements[1]);
		*time += gameData.timeDelta;
		sfVector2f scale = sfSprite_getScale(object->modsprite->sprite);
		scale.x += .1 * gameData.timeDelta;
		scale.y += .1 * gameData.timeDelta;
		sfSprite_setScale(object->modsprite->sprite, scale);
		if (*time >= MOD_CHERRYBOMB_COOLDOWN)
		{
			for (int i = 0; i < gameObjects->length; i++)
			{
				float x = object->position.x;
				float y = object->position.y;
				if (((ModObject*)(gameObjects->elements[i]))->className &&
					strcmp(((ModObject*)(gameObjects->elements[i]))->className, MOD_CLASS_ZOMBIE) == 0)
				{
					float zx = ((ModObject*)(gameObjects->elements[i]))->position.x;
					float zy = ((ModObject*)(gameObjects->elements[i]))->position.y;
					if (zx >= x - MOD_GRID_WIDTH && zx <= x + MOD_PLANT_PNG_WIDTH + MOD_GRID_WIDTH &&
						zy >= y - MOD_GRID_HEIGHT && zy <= y + MOD_PLANT_PNG_HEIGHT + MOD_GRID_HEIGHT)
						DamageZombie(gameObjects->elements[i], MOD_DAMAGE_INSTANTKILL);
				}
			}
			*health = 0;

		}
		PlantThink(object);
		if (!object)
			return;
	}
}
void JalepenoThink(ModObject* object) {
	if (object && object->data && ((ModList*)(object->data))->elements[1])
	{
		double* health = ((double*)((ModList*)object->data)->elements[0]);
		double* time = ((double*)((ModList*)(object->data))->elements[1]);
		*time += gameData.timeDelta;
		sfVector2f scale = sfSprite_getScale(object->modsprite->sprite);
		scale.x += .1 * gameData.timeDelta;
		scale.y += .1 * gameData.timeDelta;
		sfSprite_setScale(object->modsprite->sprite, scale);
		if (*time >= MOD_JALEPENO_COOLDOWN)
		{
			for (int i = 0; i < gameObjects->length; i++)
			{
				float x = object->position.x;
				float y = object->position.y;
				if (((ModObject*)(gameObjects->elements[i]))->className &&
					strcmp(((ModObject*)(gameObjects->elements[i]))->className, MOD_CLASS_ZOMBIE) == 0)
				{
					float zx = ((ModObject*)(gameObjects->elements[i]))->position.x;
					float zy = ((ModObject*)(gameObjects->elements[i]))->position.y;
					if (zy >= y && zy <= y + MOD_PLANT_PNG_HEIGHT)
						DamageZombie(gameObjects->elements[i], MOD_DAMAGE_INSTANTKILL);
				}
			}
			*health = 0;

		}
		PlantThink(object);
		if (!object)
			return;
	}
}
void ExplodeNutThink(ModObject* object) {

	if (object && object->data && ((ModList*)(object->data))->elements[1])
	{
		double* time = ((double*)((ModList*)(object->data))->elements[1]);
		if (*time == 0)
		{
			int x = (object->position.x - MOD_GRID_XPOS) / MOD_GRID_WIDTH;
			int y = (object->position.y - MOD_GRID_YPOS) / MOD_GRID_HEIGHT;
			gameData.plantGrid[y][x] = NULL;

			*time = 1;
		}
	}

	object->position.x += MOD_PROJECTILE_SPEED_NORMAL * MOD_GRID_WIDTH * gameData.timeDelta;
	ModObject_SetPosition(object, object->position);
	char hitZombie = 0;
	for (int i = 0; i < gameObjects->length; i++)
	{
		float x = object->position.x;
		float y = object->position.y;
		if (((ModObject*)(gameObjects->elements[i]))->className &&
			strcmp(((ModObject*)(gameObjects->elements[i]))->className, MOD_CLASS_ZOMBIE) == 0)
		{
			float zx = ((ModObject*)(gameObjects->elements[i]))->position.x;
			float zy = ((ModObject*)(gameObjects->elements[i]))->position.y;
			if (zx >= x && zx <= x + MOD_PLANT_PNG_WIDTH &&
				zy >= y && zy <= y + MOD_PLANT_PNG_HEIGHT)
			{
				hitZombie = 1;
				for (int i = 0; i < gameObjects->length; i++)
				{
					float x = object->position.x;
					float y = object->position.y;
					if (((ModObject*)(gameObjects->elements[i]))->className &&
						strcmp(((ModObject*)(gameObjects->elements[i]))->className, MOD_CLASS_ZOMBIE) == 0)
					{
						float zx = ((ModObject*)(gameObjects->elements[i]))->position.x;
						float zy = ((ModObject*)(gameObjects->elements[i]))->position.y;
						if (zx >= x - MOD_GRID_WIDTH && zx <= x + MOD_PLANT_PNG_WIDTH + MOD_GRID_WIDTH &&
							zy >= y - MOD_GRID_HEIGHT && zy <= y + MOD_PLANT_PNG_HEIGHT + MOD_GRID_HEIGHT)
							DamageZombie(gameObjects->elements[i], MOD_DAMAGE_INSTANTKILL);
					}
				}
				break;
			}
		}
	}
	if (hitZombie == 1 || object->position.x > MOD_WINDOW_WIDTH)
	{
		ModList_RemoveC(gameObjects, object);
		ModObject_Destroy(object);
		printf("Died :(\n");
	}
}
void RepeaterThink(ModObject* object) {
	if (object && object->data && ((ModList*)(object->data))->elements[1])
	{
		double* time = ((double*)((ModList*)(object->data))->elements[1]);
		*time += gameData.timeDelta;
		PlantThink(object);
		if (!object)
			return;
		if (*time >= MOD_REPEATER_COOLDOWN)
		{
			(*time) -= MOD_REPEATER_COOLDOWN;
			ModObject* projectile = CreateProjectile(MOD_PLANT_DAMAGE_NORMAL, MOD_PROJECTILE_SPEED_NORMAL, MOD_PEA_PNG);
			sfVector2f position = object->position;
			position.x += MOD_GRID_WIDTH;
			position.y -= (MOD_PROJECTILE_PNG_HEIGHT - MOD_GRID_HEIGHT) / 2.0;
			ModObject_SetPosition(projectile, position);
			ModList_Append(gameObjects, projectile);

			projectile = CreateProjectile(MOD_PLANT_DAMAGE_NORMAL, MOD_PROJECTILE_SPEED_NORMAL, MOD_PEA_PNG);
			position = object->position;
			position.x += MOD_GRID_WIDTH - 0.5 * MOD_GRID_WIDTH;
			position.y -= (MOD_PROJECTILE_PNG_HEIGHT - MOD_GRID_HEIGHT) / 2.0;
			ModObject_SetPosition(projectile, position);
			ModList_Append(gameObjects, projectile);
		}

	}
}
void TorchwoodThink(ModObject* object) {
	PlantThink(object);
	if (!object)
		return;
	for (int i = 0; i < gameObjects->length; i++)
	{
		float x = object->position.x;
		float y = object->position.y;
		if (((ModObject*)(gameObjects->elements[i]))->className &&
			strcmp(((ModObject*)(gameObjects->elements[i]))->className, MOD_CLASS_PROJECTILE) == 0)
		{
			float px = ((ModObject*)(gameObjects->elements[i]))->position.x;
			float py = ((ModObject*)(gameObjects->elements[i]))->position.y;
			if (px >= x && px <= x + MOD_PLANT_PNG_WIDTH &&
				py >= y && py <= y + MOD_PLANT_PNG_HEIGHT)
			{
				ModSprite_Destroy(((ModObject*)(gameObjects->elements[i]))->modsprite);
				((ModObject*)(gameObjects->elements[i]))->modsprite = ModSprite_Create(MOD_FIREPEA_PNG);
				free(((ModObject*)(gameObjects->elements[i]))->className);
				((ModObject*)(gameObjects->elements[i]))->className = NULL;
				*((double*)((ModList*)(((ModObject*)(gameObjects->elements[i]))->data))->elements[0]) *= 2;
			}
		}
	}
}
void MouseShooterThink(ModObject* object) {
	if (object && object->data && ((ModList*)(object->data))->elements[1])
	{
		double* time = ((double*)((ModList*)(object->data))->elements[1]);
		PlantThink(object);

		sfVector2i mousepos = gameData.mousepos;
		if (mousepos.x < object->position.x || mousepos.x > object->position.x + MOD_GRID_WIDTH ||
			mousepos.y < object->position.y || mousepos.y > object->position.y + MOD_GRID_HEIGHT)
		{
			return;
		}
		*time += gameData.timeDelta;
		if (!object)
			return;
		if (*time >= MOD_MOUSESHOOTER_COOLDOWN)
		{
			(*time) -= MOD_MOUSESHOOTER_COOLDOWN;
			ModObject* projectile = CreateProjectile(MOD_PLANT_DAMAGE_NORMAL, MOD_PROJECTILE_SPEED_NORMAL, MOD_PEA_PNG);
			sfVector2f position = object->position;
			position.x += MOD_GRID_WIDTH;
			position.y -= (MOD_PROJECTILE_PNG_HEIGHT - MOD_GRID_HEIGHT) / 2.0;
			ModObject_SetPosition(projectile, position);
			ModList_Append(gameObjects, projectile);

		}
	}
}
void ChomperThink(ModObject* object) {
	if (object && object->data && ((ModList*)(object->data))->elements[1])
	{
		double* time = ((double*)((ModList*)(object->data))->elements[1]);
		if(*time < MOD_CHOMPER_COOLDOWN)
			*time += gameData.timeDelta;
		PlantThink(object);
		if (!object)
			return;
		if (*time >= MOD_CHOMPER_COOLDOWN)
		{
			float x = object->position.x;
			float y = object->position.y;
			for (int i = 0; i < gameObjects->length; i++)
			{
				if (((ModObject*)(gameObjects->elements[i]))->className &&
					strcmp(((ModObject*)(gameObjects->elements[i]))->className, MOD_CLASS_ZOMBIE) == 0)
				{
					float px = ((ModObject*)(gameObjects->elements[i]))->position.x;
					float py = ((ModObject*)(gameObjects->elements[i]))->position.y;
					if (px >= x + MOD_GRID_WIDTH && px <= x + MOD_PLANT_PNG_WIDTH &&
						py >= y && py <= y + MOD_PLANT_PNG_HEIGHT)
					{
						DamageZombie(gameObjects->elements[i], MOD_DAMAGE_INSTANTKILL);
						(*time) -= MOD_CHOMPER_COOLDOWN;
						break;
					}
				}
			}
		}
	}
}
void PlantDestroy(ModObject* object) {
	for (int i = 0; i < ((ModList*)object->data)->length; i++)
	{
		free(((ModList*)object->data)->elements[i]);
	}
	ModList_Destroy(object->data);
}
ModObject* CreatePlant(int plant) {
	ModObject* object;
	double* health;
	double* time;
	switch (plant)
	{
	case MOD_SUNFLOWER:
		object = ModObject_Create(MOD_SUNFLOWER_PNG);
		object->data = ModList_Create();

		health = malloc(sizeof(double));
		time = malloc(sizeof(double));

		*health = MOD_PLANT_HEALTH_NORMAL;
		*time = 0;
		
		ModList_Append(object->data, health);
		ModList_Append(object->data, time);
		
		object->Think = SunFlowerThink;
		object->Destroy = PlantDestroy;
		break;
	case MOD_PEASHOOTER:
		object = ModObject_Create(MOD_PEASHOOTER_PNG);
		object->data = ModList_Create();

		health = malloc(sizeof(double));
		time = malloc(sizeof(double));

		*health = MOD_PLANT_HEALTH_NORMAL;
		*time = 0;

		ModList_Append(object->data, health);
		ModList_Append(object->data, time);

		object->Think = PeashooterThink;
		object->Destroy = PlantDestroy;
		break;
	case MOD_WALLNUT:
		object = ModObject_Create(MOD_WALLNUT_PNG);
		object->data = ModList_Create();

		health = malloc(sizeof(double));

		*health = MOD_PLANT_HEALTH_HIGH;

		ModList_Append(object->data, health);

		object->Think = PlantThink;
		object->Destroy = PlantDestroy;
		break;
	case MOD_CHERRYBOMB:
		object = ModObject_Create(MOD_CHERRYBOMB_PNG);
		object->data = ModList_Create();

		health = malloc(sizeof(double));
		time = malloc(sizeof(double));

		*health = MOD_PLANT_HEALTH_HIGH;
		*time = 0;
		ModList_Append(object->data, health);
		ModList_Append(object->data, time);

		object->Think = CherryBombThink;
		object->Destroy = PlantDestroy;
		break;
	case MOD_JALEPENO:
		object = ModObject_Create(MOD_JALEPENO_PNG);
		object->data = ModList_Create();

		health = malloc(sizeof(double));
		time = malloc(sizeof(double));

		*health = MOD_PLANT_HEALTH_HIGH;
		*time = 0;
		ModList_Append(object->data, health);
		ModList_Append(object->data, time);

		object->Think = JalepenoThink;
		object->Destroy = PlantDestroy;
		break;
	case MOD_EXPLODENUT:
		object = ModObject_Create(MOD_EXPLODENUT_PNG);
		object->data = ModList_Create();

		health = malloc(sizeof(double));
		time = malloc(sizeof(double));

		*health = MOD_PLANT_HEALTH_HIGH;
		*time = 0;
		ModList_Append(object->data, health);
		ModList_Append(object->data, time);

		object->Think = ExplodeNutThink;
		object->Destroy = PlantDestroy;
		break;
	case MOD_REPEATER:
		object = ModObject_Create(MOD_REPEATER_PNG);
		object->data = ModList_Create();

		health = malloc(sizeof(double));
		time = malloc(sizeof(double));

		*health = MOD_PLANT_HEALTH_NORMAL;
		*time = 0;

		ModList_Append(object->data, health);
		ModList_Append(object->data, time);

		object->Think = RepeaterThink;
		object->Destroy = PlantDestroy;
		break;
	case MOD_TORCHWOOD:
		object = ModObject_Create(MOD_TORCHWOOD_PNG);
		object->data = ModList_Create();

		health = malloc(sizeof(double)); 
		*health = MOD_PLANT_HEALTH_NORMAL;
		
		ModList_Append(object->data, health);
		
		object->Think = TorchwoodThink;
		object->Destroy = PlantDestroy;
		break;
	case MOD_MOUSESHOOTER:
		object = ModObject_Create(MOD_MOUSESHOOTER_PNG);
		object->data = ModList_Create();

		health = malloc(sizeof(double));
		time = malloc(sizeof(double));

		*health = MOD_PLANT_HEALTH_NORMAL;
		*time = 0;

		ModList_Append(object->data, health);
		ModList_Append(object->data, time);

		object->Think = MouseShooterThink;
		object->Destroy = PlantDestroy;
		break;
	case MOD_CHOMPER:
		object = ModObject_Create(MOD_CHOMPER_PNG);
		object->data = ModList_Create();

		health = malloc(sizeof(double));
		time = malloc(sizeof(double));

		*health = MOD_PLANT_HEALTH_HIGH;
		*time = MOD_CHOMPER_COOLDOWN;

		ModList_Append(object->data, health);
		ModList_Append(object->data, time);

		object->Think = ChomperThink;
		object->Destroy = PlantDestroy;
		break;
	default:
		return NULL;
	}

	return object;
}