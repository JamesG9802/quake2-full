#pragma once

#include "ModObject.h"
#include "ModObjectUI.h"

ModObject* CreateModUI(char* imagepath)
{
	return ModObject_Create(imagepath);
}