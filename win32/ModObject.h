#pragma once

/*	SFML Stuff	*/
#include "SFML/System/Vector2.h"

/*	My Stuff	*/
#include "ModSprite.h"
#include "ModObject.h"

struct ModObject;
/// <summary>
/// ModObjects are structs that are able to think during each game tick and can draw to the screen.
/// </summary
typedef struct ModObject {
	ModSprite* modsprite;
	sfVector2f position;
	void (*Think)(struct ModObject*);

	//	Unusued variable for other classes
	sfVector2f vectorData;
} ModObject;

/// <summary>
/// Create a mod object without a sprite;
/// </summary>
/// <returns></returns>
ModObject* ModObject_CreateNoSprite();
ModObject* ModObject_Create(const char* sprite);
void ModObject_Destroy(ModObject* object);
void ModObject_Think(ModObject* object);
void ModObject_Draw(ModObject* object, sfRenderWindow* window);
void ModObject_SetPosition(ModObject* object, sfVector2f position);
void ModObject_Resize(ModObject* object, sfVector2f size);