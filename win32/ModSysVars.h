#pragma once
/*	Contains Important System variables for the Win32 api	*/


struct sysvars {
	int mouseX;	//	x position of the cursor
	int mouseY;	//	y position of the cursor
};

struct sysvars SystemVars;

int GetMouseX()
{
	return SystemVars.mouseX;
}
void SetMouseX(int x)
{
	SystemVars.mouseX = x;
}
int GetMouseY()
{
	return SystemVars.mouseY;
}

void SetMouseY(int y)
{
	SystemVars.mouseY = y;
}