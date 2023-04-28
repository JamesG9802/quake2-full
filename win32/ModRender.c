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
#include "ModPriorityQueue.h"
void ModRenderInit()
{
	sfVideoMode vidMode;
	vidMode.width = MOD_WINDOW_WIDTH;
	vidMode.height = MOD_WINDOW_HEIGHT;
	window = sfRenderWindow_create(vidMode, "Totally Quake :)", sfClose | sfTitlebar, NULL);
	sfRenderWindow_setVerticalSyncEnabled(window, true);
}
/// <summary>
/// Draw Game Objects first and then UI over it
/// </summary>
void ModRenderUpdate()
{
	for (int i = 0; i < gameObjects->length; i++)
	{
		ModObject_Draw(((ModObject*)(gameObjects->elements[i])), window);
	}
	for (int i = 0; i < uiObjects->length; i++)
	{
		ModObject_Draw((ModObject*)(ModPriorityQueue_At(uiObjects, i)), window);
	}
	sfRenderWindow_display(window);
	sfRenderWindow_clear(window, sfBlack);
}

void ModRenderResize(sfEvent event)
{
	sfFloatRect rect;
	sfView* view;
	rect.top = 0;
	rect.left = 0;
	rect.width = event.size.width;
	rect.height = event.size.height;
//	view = sfView_createFromRect(rect);
//	sfRenderWindow_setView(window, view);
//	sfView_destroy(view);
}
