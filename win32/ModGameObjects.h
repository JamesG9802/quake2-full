#pragma once

#include "SFML/Graphics.h"
#include "SFML/Graphics/RectangleShape.h"
#include "SFML/Graphics/Color.h"
#include "SFML/System/Vector2.h"

#include "ModDefs.h"
#include "ModSysVars.h"
#include "ModObject.h"

void GridThink(ModObject* object) {
	sfRectangleShape* rect = sfRectangleShape_create();

	if (!object) return;

	/*	Doesn't work because render immediately clears
	sfRectangleShape_setFillColor(rect, sfRed);
	sfRectangleShape_setPosition(rect, object->position);
	sfRenderWindow_drawRectangleShape(window, rect, NULL);
	*/
	sfVector2i mousepos = sfMouse_getPositionRenderWindow(window);
	
	/*	Outside the bounds	*/
	if (mousepos.x < object->position.x || mousepos.x > object->position.x + MOD_GRID_WIDTH ||
		mousepos.y < object->position.y || mousepos.y > object->position.y + MOD_GRID_HEIGHT)
		return;
	printf("%d %d\n", (mousepos.x - MOD_GRID_XPOS) / MOD_GRID_WIDTH, 
		(mousepos.y - MOD_GRID_YPOS) / MOD_GRID_HEIGHT);
}