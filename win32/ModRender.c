/*	Quake Stuff	*/
#include "../qcommon/qcommon.h"

/*	SFML Stuff */
#include <SFML/Graphics.h>

/*	My Stuff	*/
#include "ModSysVars.h"
#include "ModRender.h"

extern sfTexture* texture = NULL;
extern sfSprite* sprite = NULL;

void ModRenderInit()
{
	sfVideoMode vidMode;
	byte* memory;
	int size = -1;
	vidMode.width = 200;
	vidMode.height = 200;
	window = sfRenderWindow_create(vidMode, "Totally Quake :)", sfDefaultStyle, NULL);

	size = FS_LoadFile("pics/happy.png", (void**)&memory);
	if (size == -1)
	{
		printf("SOMETHING WENT WRONG D:");
		return;
	}
	printf("Size in bytes: %d\n", size);
	for (int i = 0; i < size; i++)
	{
		printf("%02hhx ", memory[i]);
	}
	texture = sfTexture_createFromMemory(memory, size, NULL);
	FS_FreeFile(memory);
	if (!texture) return;
	sprite = sfSprite_create();
	sfSprite_setTexture(sprite, texture, true);
}
void ModRenderUpdate()
{
	sfRenderWindow_clear(window, sfBlack);
	if (sprite)
	sfRenderWindow_drawSprite(window, sprite, NULL);
	sfRenderWindow_display(window);
}