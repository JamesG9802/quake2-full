#pragma once

#include <SFML/Graphics.h>
#include <SFML/Window.h>

/*	Contains Important System variables for the Mod	*/

/// <summary>
/// Whether the application should close
/// </summary>
int exitFlag;

/// <summary>
/// Singleton instance of the main window of the application.
/// </summary>
struct sfRenderWindow* window;