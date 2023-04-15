/*	Quake Stuff	*/
#include "../qcommon/qcommon.h"

/*	SFML Stuff */
#include <SFML/Graphics.h>

/*	My Stuff	*/
#include "ModSysVars.h"
#include "ModRender.h"
#include "ModSprite.h"
#include "ModGame.h"

extern ModSprite* modsprite = NULL;

void ModRenderInit()
{
	sfVideoMode vidMode;
	vidMode.width = 600;
	vidMode.height = 600;
	window = sfRenderWindow_create(vidMode, "Totally Quake :)", sfDefaultStyle, NULL);
	sfRenderWindow_setVerticalSyncEnabled(window, true);
}
void ModRenderUpdate()
{
	sfRenderWindow_clear(window, sfBlack);
	if (object)
	{
		ModObject_Draw(object, window);
	}
	sfRenderWindow_display(window);
}