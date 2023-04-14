#pragma once

sfTexture* texture;
sfSprite* sprite;
/// <summary>
/// Initializes the window of the application.
/// </summary>
void ModRenderInit();

/// <summary>
/// Renders all relevant sprites to the window
/// </summary>
void ModRenderUpdate();