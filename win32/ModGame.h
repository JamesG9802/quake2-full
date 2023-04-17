#pragma once

#include "ModObject.h"
#include "ModList.h"

ModList* gameObjects;

/// <summary>
/// Initializes game by binding common actions
/// </summary>
void ModGameInit();
/// <summary>/// Primary action /// </summary>
void (*Primary_Action)(void);
/// <summary>/// Secondary action /// </summary>
void (*Secondary_Action)(void);
void ModGameUpdate();
void ModGameCleanup();