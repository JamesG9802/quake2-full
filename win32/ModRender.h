#pragma once

#include "ModSprite.h"

/// <summary>
/// Initializes the window of the application.
/// </summary>
void ModRenderInit();

/// <summary>
/// Renders all relevant sprites to the window
/// </summary>
void ModRenderUpdate();

void ModRenderResize(sfEvent event);