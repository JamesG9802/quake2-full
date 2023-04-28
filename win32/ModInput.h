#pragma once

#include <SFML/Window.h>

#include "ModGame.h"

/// <summary>
/// Due to binding commands dealing with exclusively key or mouse, we wrap them up in an abstraction layer
/// </summary>
typedef struct sfInput {
	//	0 = key, 1 = mouse
	char isMouse;
	sfKeyCode keycode;
	sfMouseButton buttoncode;
} sfInput;

/// <summary>
/// Checks if an input is pressed
/// </summary>
int isPressed(sfInput input);

/*	List of verbs	*/

sfInput primary;
sfInput secondary;
sfInput left;
sfInput right;


/// <summary>
/// Queue inputs to execute.
/// </summary>
void ModInput_Update();

/// <summary>
/// Rebind a key to a given command.
/// </summary>
void ModInput_Rebind(const char* key, const char* command);

/// <summary>
/// Converts a string to a keycode
/// </summary>
/// <param name="key"></param>
/// <returns></returns>
sfKeyCode stringToKeyCode(const char* string, int length);

/// <summary>
/// Converts a string to a mouse button
/// </summary>
/// <param name="key"></param>
/// <returns></returns>
sfMouseButton stringToMouseButton(const char* string);