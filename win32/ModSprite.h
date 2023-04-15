#pragma once
#include <SFML/Graphics.h>
typedef struct ModSprite {
	sfTexture* texture;
	sfSprite* sprite;
} ModSprite;

/// <summary>
/// Try to create a ModSprite. Returns NULL upon failure.
/// </summary>
/// <param name="filepath"></param>
/// <returns></returns>
ModSprite* ModSprite_Create(const char* filepath);

/// <summary>
/// If a modsprite exists, free its allocated memory
/// </summary>
/// <param name="modsprite"></param>
void ModSprite_Destroy(ModSprite* modsprite);