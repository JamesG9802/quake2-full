#pragma once

#include "SFML/Graphics.h"
#include "SFML/Graphics/RectangleShape.h"
#include "SFML/Graphics/Color.h"
#include "SFML/System/Vector2.h"

#include "ModGame.h"
#include "ModDefs.h"
#include "ModSysVars.h"
#include "ModObject.h"
#include "ModPlant.h"

/*	Utility Class containing common game object related functions*/


/// <summary>
/// Places a plant given its grid coordinates
/// </summary>
/// <returns></returns>
ModObject* PlacePlant(ModObject* object, int x, int y);

void SunThink(ModObject* object);
ModObject* CreateSun();
/// <summary>
/// Think function for the grid squares
/// </summary>
/// <param name="object"></param>
void GridThink(ModObject* object);
void GameThink(ModObject* object);