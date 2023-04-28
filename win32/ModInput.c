#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include <SFML/Window.h>

#include "ModInput.h"
#include "ModGame.h"

/*	Helper Method	*/	
sfInput ModInput_ConvertToInput(const char* key)
{
	sfInput input;

	if (stringToKeyCode(key, strlen(key)) != sfKeyUnknown)
	{
		input.isMouse = 0;
		input.keycode = stringToKeyCode(key, strlen(key));
	}
	else
	{
		input.isMouse = 1; 
		input.buttoncode = stringToMouseButton(key, strlen(key));
	}
	return input;
}
int isPressed(sfInput input)
{
	if (input.isMouse)
		return sfMouse_isButtonPressed(input.buttoncode);
	return sfKeyboard_isKeyPressed(input.keycode);
}
void ModInput_Update()
{
	//	PRIMARY
	if (isPressed(primary))	{
		gameData.primaryDown = 1;
		gameData.primaryReleased = 0;
	}
	else if (gameData.primaryDown == 1)	{
		gameData.primaryDown = 0;
		gameData.primaryReleased = 1;
	}
	else	{
		gameData.primaryDown = 0;
		gameData.primaryReleased = 0;
	}
	//	SECONDARY
	if (isPressed(secondary)) {
		gameData.secondaryDown = 1;
		gameData.secondaryReleased = 0;
	}
	else if (gameData.secondaryDown == 1) {
		gameData.secondaryDown = 0;
		gameData.secondaryReleased = 1;
	}
	else{
		gameData.secondaryDown = 0;
		gameData.secondaryReleased = 0;
	}
	//	LEFT
	if (isPressed(left)) {
		gameData.leftDown = 1;
		gameData.leftReleased = 0;
	}
	else if (gameData.leftDown == 1) {
		gameData.leftDown = 0;
		gameData.leftReleased = 1;
	}
	else {
		gameData.leftDown = 0;
		gameData.leftReleased = 0;
	}
	//	RIGHT
	if (isPressed(right)) {
		gameData.rightDown = 1;
		gameData.rightReleased = 0;
	}
	else if (gameData.rightDown == 1) {
		gameData.rightDown = 0;
		gameData.rightReleased = 1;
	}
	else {
		gameData.rightDown = 0;
		gameData.rightReleased = 0;
	}
}
void ModInput_Rebind(const char* key, const char* command)
{
	if (command == 0)
		return;
	if (strcmp(command, "primary") == 0)
		primary = ModInput_ConvertToInput(key);
	else if (strcmp(command, "secondary") == 0)
		secondary = ModInput_ConvertToInput(key);
	else if (strcmp(command, "left") == 0)
		left = ModInput_ConvertToInput(key);
	else if (strcmp(command, "right") == 0)
		right = ModInput_ConvertToInput(key);
}

sfKeyCode stringToKeyCode(const char* string, int length)
{
	if (length == 0)
		return sfKeyUnknown;
	if (length == 1)	//	Single character keys
	{
		char key = string[0];
		key = tolower(key);
		if (isalpha(key))	//	keycodes for letters start at 0
			return (sfKeyCode)(key - 'a');
		if (isdigit(key))	//	keycodes for number start at 26
			return (sfKeyCode)(key - '0' + 26);
		//	Rest of the weird characters
		switch (key)
		{
		case '\'':
			return sfKeyQuote;
		case '+':
			return sfKeyAdd;
		case ',':
			return sfKeyComma;
		case '-':
			return sfKeySubtract;
		case '.':
			return sfKeyPeriod;
		case '/':
			return sfKeySlash;
		case '=':
			return sfKeyEqual;
		case '[':
			return sfKeyLBracket;
		case '\\':
			return sfKeyBackslash;
		case ']':
			return sfKeyRBracket;
		case '`':
			return sfKeyTilde;
		default:
			return sfKeyUnknown;
		}
	}
	else
	{
		char* lowerstring;
		sfKeyCode keycode = sfKeyUnknown;
		lowerstring = malloc(strlen(string) + 1);
		strcpy(lowerstring, string);
		for (int i = 0; lowerstring[i]; i++)
			lowerstring[i] = tolower(lowerstring[i]);
		if (strcmp(lowerstring, "tab") == 0)
			keycode = sfKeyTab;
		else if (strcmp(lowerstring, "enter") == 0)
			keycode = sfKeyEnter;
		else if (strcmp(lowerstring, "escape") == 0)
			keycode = sfKeyEscape;
		else if (strcmp(lowerstring, "space") == 0)
			keycode = sfKeySpace;
		else if (strcmp(lowerstring, "backspace") == 0)
			keycode = sfKeyBackspace;
		else if (strcmp(lowerstring, "uparrow") == 0)
			keycode = sfKeyUp;
		else if (strcmp(lowerstring, "downarrow") == 0)
			keycode = sfKeyDown;
		else if (strcmp(lowerstring, "leftarrow") == 0)
			keycode = sfKeyLeft;
		else if (strcmp(lowerstring, "rightarrow") == 0)
			keycode = sfKeyRight;
		else if (strcmp(lowerstring, "alt") == 0)
			keycode = sfKeyLAlt;
		else if (strcmp(lowerstring, "ctrl") == 0)
			keycode = sfKeyLControl;
		else if (strcmp(lowerstring, "shift") == 0)
			keycode = sfKeyLShift;
		else if (strcmp(lowerstring, "f1") == 0)
			keycode = sfKeyF1;
		else if (strcmp(lowerstring, "f2") == 0)
			keycode = sfKeyF2;
		else if (strcmp(lowerstring, "f3") == 0)
			keycode = sfKeyF3;
		else if (strcmp(lowerstring, "f4") == 0)
			keycode = sfKeyF4;
		else if (strcmp(lowerstring, "f5") == 0)
			keycode = sfKeyF5;
		else if (strcmp(lowerstring, "f6") == 0)
			keycode = sfKeyF6;
		else if (strcmp(lowerstring, "f7") == 0)
			keycode = sfKeyF7;
		else if (strcmp(lowerstring, "f8") == 0)
			keycode = sfKeyF8;
		else if (strcmp(lowerstring, "f9") == 0)
			keycode = sfKeyF9;
		else if (strcmp(lowerstring, "f10") == 0)
			keycode = sfKeyF10;
		else if (strcmp(lowerstring, "f11") == 0)
			keycode = sfKeyF11;
		else if (strcmp(lowerstring, "f12") == 0)
			keycode = sfKeyF12;
		else if (strcmp(lowerstring, "ins") == 0)
			keycode = sfKeyInsert;
		else if (strcmp(lowerstring, "del") == 0)
			keycode = sfKeyDelete;
		else if (strcmp(lowerstring, "pgdn") == 0)
			keycode = sfKeyPageDown;
		else if (strcmp(lowerstring, "pgup") == 0)
			keycode = sfKeyPageUp;
		else if (strcmp(lowerstring, "end") == 0)
			keycode = sfKeyEnd;
		else if (strcmp(lowerstring, "pause") == 0)
			keycode = sfKeyPause;
		free(lowerstring);
		return keycode;
	}
}

sfMouseButton stringToMouseButton(const char* string)
{
	char* lowerstring;
	sfMouseButton button = sfMouseLeft;
	lowerstring = malloc(strlen(string) + 1);
	strcpy(lowerstring, string);
	for (int i = 0; lowerstring[i]; i++)
		lowerstring[i] = tolower(lowerstring[i]);

	if (strcmp(lowerstring, "mouse1") == 0)
		button = sfMouseLeft;
	else if (strcmp(lowerstring, "mouse2") == 0)
		button = sfMouseRight;
	else if (strcmp(lowerstring, "mouse3") == 0)
		button = sfMouseMiddle;
	else if (strcmp(lowerstring, "mouse4") == 0)
		button = sfMouseXButton1;
	else if (strcmp(lowerstring, "mouse5") == 0)
		button = sfMouseXButton2;
	free(lowerstring);
	return button;
}