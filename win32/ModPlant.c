#include <stdio.h>
#include <stdlib.h>

#include "ModDefs.h"
#include "ModGame.h"
#include "ModObject.h"
#include "ModGameObjects.h"
#include "ModPlant.h"

void PlantThink(ModObject* object) {
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
		if (*time >= 5)
		{
			(*time)-= 5;
			ModObject* sun = CreateSun();
			sfVector2f position = object->position;
			position.x += (((float)rand() / (float)(RAND_MAX / 2)) - 1) * 30;
			position.y += (((float)rand() / (float)(RAND_MAX / 2)) - 1) * 30;
			ModObject_SetPosition(sun, position);
			ModList_Append(gameObjects, sun);
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
	default:
		return NULL;
	}

	return object;
}