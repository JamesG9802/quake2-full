#pragma once

#include <stdio.h>

/*	Quake Stuff	*/
#include "../qcommon/qcommon.h"

#include <SFML/Graphics.h>
#include <SFML/Graphics/Color.h>
#include <SFML/Graphics/Font.h>
#include <SFML/System/Types.h>
#include <SFML/System/Vector2.h>

#include "ModDefs.h"
#include "ModGame.h"
#include "ModObject.h"
#include "ModObjectUI.h"
#include "ModSysVars.h"


/// <summary>
/// Think Function for the Sun Counter
/// </summary>
/// <param name="object"></param>
void SunCounter_Think(ModObject* object)
{
	static int isInitialized = 0;

	ModList* list = (ModList*)(object->data);
	sfFont* font = (sfFont*)(list->elements[0]);
	sfText* text = (sfText*)(list->elements[1]);
	unsigned char* memory = (char*)(list->elements[2]);

	if (!isInitialized)
	{
		int size = -1;
		isInitialized = 1;

		size = FS_LoadFile(MOD_TEXTBOLD_TTF, (void**)&memory);
		if (size == -1)
			return;
		font = sfFont_createFromMemory(memory, size);

		text = sfText_create();
		sfText_setFont(text, font);
		sfText_setFillColor(text, sfBlack);
		sfText_setCharacterSize(text, 24);
		sfVector2f pos;
		pos.x = 8;
		pos.y = 5;
		sfText_setPosition(text, pos);

		((ModList*)(object->data))->elements[0] = font;
		((ModList*)(object->data))->elements[1] = text;
		((ModList*)(object->data))->elements[2] = memory;
	}
	char buffer[32];
	sprintf(buffer, "%lu", gameData.sunAmt);
	sfText_setString(text, buffer);
}
void SunCounter_Draw(ModObject* object)
{
	ModList* list = (ModList*)(object->data);
	sfText* text = (sfText*)(list->elements[1]);
	sfRenderWindow_drawText(window, text, NULL);
}
void SunCounter_Destroy(ModObject* object)
{
	sfFont_destroy(((ModList*)(object->data))->elements[0]);
	sfText_destroy(((ModList*)(object->data))->elements[1]);
	FS_FreeFile(((ModList*)(object->data))->elements[2]);
}
ModObject* UI_CreateSunCounter()
{
	/*	Init Image	*/
	ModObject* ui = ModObject_Create(MOD_SUN_PNG);
	sfVector2f scale;
	scale.x = (float)MOD_GRID_WIDTH / MOD_PLANT_PNG_WIDTH;
	scale.y = (float)MOD_GRID_WIDTH / MOD_PLANT_PNG_WIDTH;
	ModObject_Resize(ui, scale);

	/*	Set Up Specific Functions	*/
	ui->Think = SunCounter_Think;
	ui->Draw = SunCounter_Draw;
	ui->Destroy = SunCounter_Destroy;

	/*	Using data to represent a list	*/
	ui->data = ModList_Create();
	ModList_Append(ui->data, NULL);		//	sfFont*
	ModList_Append(ui->data, NULL);		//	sfText*
	ModList_Append(ui->data, NULL);		//	unsigned char*
	return ui;
}