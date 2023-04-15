#pragma once

/*	Quake Stuff	*/
#include "../qcommon/qcommon.h"

/*	SFML Stuff */
#include <SFML/Graphics.h>
#include <SFML/System/Vector2.h>

/*	My Stuff	*/
#include "ModSprite.h"
#include "ModObject.h"

ModObject* ModObject_CreateNoSprite()
{
	ModObject* obj = malloc(sizeof(ModObject));
	if (!obj) return obj;
	obj->modsprite = NULL;
	obj->Think = NULL;
	obj->position.x = 0;
	obj->position.y = 0;
	return obj;
}
ModObject* ModObject_Create(const char* sprite)
{
	ModObject* obj = ModObject_CreateNoSprite();
	obj->modsprite = ModSprite_Create(sprite);
	return obj;
}
void ModObject_Destroy(ModObject* object)
{
	if (object == NULL)
		return;
	if (object->modsprite)
		ModSprite_Destroy(object->modsprite);
	free(object);
}
void ModObject_Think(ModObject* object)
{
	if (object && object->Think) object->Think();
}
void ModObject_Draw(ModObject* object, sfRenderWindow* window)
{
	if (object && object->modsprite) 
	{
		sfSprite_setPosition(object->modsprite->sprite, object->position);
		sfRenderWindow_drawSprite(window, object->modsprite->sprite, NULL);
	}
}