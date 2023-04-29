#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ModDefs.h"
#include "ModList.h"
#include "ModGame.h"
#include "ModObject.h"
#include "ModZombie.h"

void DamageZombie(ModObject* zombie, double damage) {
	if (zombie && ((ModList*)zombie->data)->elements[0])
	{
		double* health = ((double*)((ModList*)zombie->data)->elements[0]);
		*health -= damage;
		sfSprite_setColor(zombie->modsprite->sprite, sfRed);
	}
}
void DamagePlant(ModObject* zombie, ModObject* plant) {
	if (zombie && plant &&
		zombie->data && plant->data &&
		((ModList*)zombie->data)->elements[1] && ((ModList*)plant->data)->elements[0])
	{
		double damage = *((double*)((ModList*)zombie->data)->elements[1]);
		double health = *((double*)((ModList*)plant->data)->elements[0]);
		health -= damage * gameData.timeDelta;
		*((double*)((ModList*)plant->data)->elements[0]) = health;
		sfSprite_setColor(plant->modsprite->sprite, sfRed);
	}
}

void ZombieThink(ModObject* object) {
	sfVector2f pos;

	if (object->data && ((ModList*)(object->data))->elements[0]) {
		double health = *((double*)((ModList*)object->data)->elements[0]);
		if (health <= 0)
		{
			ModList_RemoveC(gameObjects, object);
			ModObject_Destroy(object);
			return;
		}
	}
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

	int x = (object->position.x - MOD_GRID_XPOS) / MOD_GRID_WIDTH;
	int y = (object->position.y - MOD_GRID_YPOS) / MOD_GRID_HEIGHT;
	if (x >= MOD_GRID_COLS || y >= MOD_GRID_ROWS)
		;
	else if(gameData.plantGrid[y][x])
	{
		DamagePlant(object, gameData.plantGrid[y][x]);
		return;
	}

	double speed = *((double*)((ModList*)(object->data))->elements[2]);	//	grid per seconds
	speed *= MOD_GRID_WIDTH;
	pos.x = object->position.x - gameData.timeDelta * speed;
	pos.y = object->position.y;
	ModObject_SetPosition(object, pos);
}

void ZombieDestroy(ModObject* object) {
	for (int i = 0; i < ((ModList*)object->data)->length; i++)
	{
		free(((ModList*)object->data)->elements[i]);
	}
	ModList_Destroy(object->data);
}
ModObject* CreateZombie(int zombie) {
	ModObject* object;
	double* health;
	double* damage;
	double* speed;
	switch (zombie) {
	case MOD_ZOMBIE_REGULAR:
		object = ModObject_Create(MOD_ZOMBIE_REGULAR_PNG);
		object->className = malloc(sizeof(char)*(strlen(MOD_CLASS_ZOMBIE)+1));
		strcpy(object->className, MOD_CLASS_ZOMBIE);
		object->data = ModList_Create();
		health = malloc(sizeof(double));
		damage = malloc(sizeof(double));
		speed = malloc(sizeof(double));

		*health = MOD_ZOMBIE_HEALTH_LOW;
		*damage = MOD_ZOMBIE_DAMAGE_NORMAL;
		*speed = MOD_ZOMBIE_SPEED_NORMAL;

		ModList_Append(object->data, health);
		ModList_Append(object->data, damage);
		ModList_Append(object->data, speed);

		object->Think = ZombieThink;
		object->Destroy = ZombieDestroy;

		break;
	case MOD_ZOMBIE_CONE:
		object = ModObject_Create(MOD_ZOMBIE_CONE_PNG);
		object->className = malloc(sizeof(char) * (strlen(MOD_CLASS_ZOMBIE) + 1));
		strcpy(object->className, MOD_CLASS_ZOMBIE);
		object->data = ModList_Create();
		health = malloc(sizeof(double));
		damage = malloc(sizeof(double));
		speed = malloc(sizeof(double));

		*health = MOD_ZOMBIE_HEALTH_NORMAL;
		*damage = MOD_ZOMBIE_DAMAGE_NORMAL;
		*speed = MOD_ZOMBIE_SPEED_NORMAL;

		ModList_Append(object->data, health);
		ModList_Append(object->data, damage);
		ModList_Append(object->data, speed);

		object->Think = ZombieThink;
		object->Destroy = ZombieDestroy;

		break;
	case MOD_ZOMBIE_BUCKET:
		object = ModObject_Create(MOD_ZOMBIE_BUCKET_PNG);
		object->className = malloc(sizeof(char) * (strlen(MOD_CLASS_ZOMBIE) + 1));
		strcpy(object->className, MOD_CLASS_ZOMBIE);
		object->data = ModList_Create();
		health = malloc(sizeof(double));
		damage = malloc(sizeof(double));
		speed = malloc(sizeof(double));

		*health = MOD_ZOMBIE_HEALTH_HIGH;
		*damage = MOD_ZOMBIE_DAMAGE_NORMAL;
		*speed = MOD_ZOMBIE_SPEED_NORMAL;

		ModList_Append(object->data, health);
		ModList_Append(object->data, damage);
		ModList_Append(object->data, speed);

		object->Think = ZombieThink;
		object->Destroy = ZombieDestroy;

		break;
	case MOD_ZOMBIE_FLAG:
		object = ModObject_Create(MOD_ZOMBIE_FLAG_PNG);
		object->className = malloc(sizeof(char) * (strlen(MOD_CLASS_ZOMBIE) + 1));
		strcpy(object->className, MOD_CLASS_ZOMBIE);
		object->data = ModList_Create();
		health = malloc(sizeof(double));
		damage = malloc(sizeof(double));
		speed = malloc(sizeof(double));

		*health = MOD_ZOMBIE_HEALTH_NORMAL;
		*damage = MOD_ZOMBIE_DAMAGE_NORMAL;
		*speed = MOD_ZOMBIE_SPEED_HIGH;

		ModList_Append(object->data, health);
		ModList_Append(object->data, damage);
		ModList_Append(object->data, speed);

		object->Think = ZombieThink;
		object->Destroy = ZombieDestroy;

		break;
	case MOD_ZOMBIE_FOOTBALL:
		object = ModObject_Create(MOD_ZOMBIE_FOOTBALL_PNG);
		object->className = malloc(sizeof(char) * (strlen(MOD_CLASS_ZOMBIE) + 1));
		strcpy(object->className, MOD_CLASS_ZOMBIE);
		object->data = ModList_Create();
		health = malloc(sizeof(double));
		damage = malloc(sizeof(double));
		speed = malloc(sizeof(double));

		*health = MOD_ZOMBIE_HEALTH_HIGH;
		*damage = MOD_ZOMBIE_DAMAGE_NORMAL;
		*speed = MOD_ZOMBIE_SPEED_HIGH;

		ModList_Append(object->data, health);
		ModList_Append(object->data, damage);
		ModList_Append(object->data, speed);

		object->Think = ZombieThink;
		object->Destroy = ZombieDestroy;

		break;
	default:
		return NULL;
	}
	return object;
}