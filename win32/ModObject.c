
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
	obj->Draw = NULL;
	obj->Destroy = NULL;
	obj->shouldDraw = 0;
	obj->position.x = 0;
	obj->position.y = 0;
	return obj;
}
ModObject* ModObject_Create(const char* sprite)
{
	ModObject* obj = ModObject_CreateNoSprite();
	obj->modsprite = ModSprite_Create(sprite);
	obj->shouldDraw = 1;
	return obj;
}
void ModObject_Destroy(ModObject* object)
{
	if (object == NULL)
		return;
	if (object->Destroy)
		object->Destroy(object);
	if (object->modsprite)
		ModSprite_Destroy(object->modsprite);
	free(object);
}
void ModObject_Think(ModObject* object)
{
	if (object && object->Think) object->Think(object);
}
void ModObject_Draw(ModObject* object, sfRenderWindow* window)
{
	if (!object || object && !object->shouldDraw)
		return;
	if (!object->Draw && object->modsprite)	//	using default draw
	{
		sfRenderWindow_drawSprite(window, object->modsprite->sprite, NULL);
	}
	else if(object->Draw)	// custom draw
		object->Draw(object);
}
void ModObject_SetPosition(ModObject* object, sfVector2f position)
{
	if(object)
		object->position = position;
	if (object && object->modsprite)
		sfSprite_setPosition(object->modsprite->sprite, object->position);
}
void ModObject_Resize(ModObject* object, sfVector2f size)
{
	if (object && object->modsprite)
		sfSprite_setScale(object->modsprite->sprite, size);
}