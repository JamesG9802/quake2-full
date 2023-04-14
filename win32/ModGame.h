#pragma once

/// <summary>
/// Initializes game by binding common actions
/// </summary>
void ModGameInit();
/// <summary>/// Primary action /// </summary>
void (*Primary_Action)(void);
/// <summary>/// Secondary action /// </summary>
void (*Secondary_Action)(void);