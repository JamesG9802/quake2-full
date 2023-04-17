/*	Quake Stuff	*/
#include "../qcommon/qcommon.h"

/*	SFML Stuff */
#include <SFML/Graphics.h>
#include <SFML/Graphics/Rect.h>
#include <SFML/Window/Event.h>

/*	My Stuff	*/
#include "ModSysVars.h"
#include "ModRender.h"
#include "ModSprite.h"
#include "ModGame.h"
#include "ModObject.h"
#include "ModList.h"

void ModRenderInit()
{
	sfVideoMode vidMode;
	vidMode.width = 800;
	vidMode.height = 600;
	window = sfRenderWindow_create(vidMode, "Totally Quake :)", sfDefaultStyle, NULL);
	sfRenderWindow_setVerticalSyncEnabled(window, true);
}
void ModRenderUpdate()
{
	sfRenderWindow_clear(window, sfBlack);
	for (int i = 0; i < gameObjects->length; i++)
	{
		ModObject_Draw(((ModObject*)(gameObjects->elements[i])), window);
	}
	sfRenderWindow_display(window);
}

void ModRenderResize(sfEvent event)
{
	sfFloatRect rect;
	sfView* view;
	rect.top = 0;
	rect.left = 0;
	rect.width = event.size.width;
	rect.height = event.size.height;
	view = sfView_createFromRect(rect);
	sfRenderWindow_setView(window, view);
	sfView_destroy(view);
}
