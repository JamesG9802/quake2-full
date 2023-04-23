#include <stdio.h>
#include <stdlib.h>

#include "ModDefs.h"
#include "ModGame.h"
#include "ModObject.h"
#include "ModGameObjects.h"
#include "ModPlant.h"

void SunFlowerThink(ModObject* object) {
	static float time = 0;
	time += gameData.timeDelta;
	if (time >= 1)
	{
		time--;
		printf("spawning sun\n");
		ModObject* sun = CreateSun();
		sfVector2f position = object->position;
		position.x += (((float)rand() / (float)(RAND_MAX / 2)) - 1) * 30;
		position.y += (((float)rand() / (float)(RAND_MAX / 2)) - 1) * 30;
		ModObject_SetPosition(sun, position);
		ModList_Append(gameObjects, sun);
	}
}
ModObject* CreatePlant(int plant) {
	ModObject* object;
	switch (plant)
	{
	case MOD_SUNFLOWER:
		object = ModObject_Create(MOD_SUNFLOWER_PNG);
		object->Think = SunFlowerThink;
		break;
	case MOD_PEASHOOTER:
		object = ModObject_Create(MOD_PEASHOOTER_PNG);
		break;
	default:
		return NULL;
	}

	return object;
}