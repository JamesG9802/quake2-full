#include "../qcommon/qcommon.h"
#include "ModRender.h"
#include <SFML/Graphics.h>


sfRenderWindow* window;
void ModRenderInit()
{
	sfVideoMode vidMode;
	vidMode.width = 200;
	vidMode.height = 200;
	window = sfRenderWindow_create(vidMode, "Totally Quake :)", sfDefaultStyle, NULL);
}