#include <stdlib.h>
#include <stdio.h>

#include <SFML/Window.h>

#include "ModGame.h"
#include "ModSysVars.h"

extern void (*Primary_Action)(void);
extern void (*Secondary_Action)(void);

void Game_Primary()
{
	printf("primary action\n");
}
void Game_Secondary()
{
	printf("Secondary action\n");
}

void ModGameInit()
{
	Primary_Action = Game_Primary;
	Secondary_Action = Game_Secondary;
	object = ModObject_Create("pics/happy.png");
}
void ModGameUpdate()
{
	object->position.x = sfMouse_getPositionRenderWindow(window).x;
	object->position.y = sfMouse_getPositionRenderWindow(window).y;

	printf("%.6f %.6f\n", object->position.x, object->position.y);
}
void ModGameCleanup()
{
	ModObject_Destroy(object);
}