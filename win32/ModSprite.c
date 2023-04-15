/*	Quake Stuff	*/
#include "../qcommon/qcommon.h"

/*	SFML Stuff */
#include <SFML/Graphics.h>

/*	My Stuff	*/
#include "ModSprite.h"

ModSprite* ModSprite_Create(const char* filepath)
{
	/*	Because Quake stores files in .pak files, we can only load the bytes to create the sprites */
	ModSprite* modsprite = NULL;
	unsigned char* memory;
	int size = -1;

	sfTexture* texture;
	sfSprite* sprite;

	size = FS_LoadFile(filepath, (void**)&memory);
	if (size == -1)
		return NULL;
	texture = sfTexture_createFromMemory(memory, size, NULL);
	FS_FreeFile(memory);
	if (!texture)
		return NULL;

	sprite = sfSprite_create();
	if (!sprite)
	{
		sfTexture_destroy(texture);
		return NULL;
	}
	sfSprite_setTexture(sprite, texture, true);
	/*	At this point, both texture and sprite are guaranteed to exist	*/
	modsprite = malloc(sizeof(ModSprite));
	if (!modsprite)
		return NULL;
	modsprite->texture = texture;
	modsprite->sprite = sprite;
	return modsprite;
}
void ModSprite_Destroy(ModSprite* modsprite)
{
	if (modsprite)
	{
		if (modsprite->texture)
			sfTexture_destroy(modsprite->texture);
		if (modsprite->sprite)
			sfSprite_destroy(modsprite->sprite);
		free(modsprite);
	}
}