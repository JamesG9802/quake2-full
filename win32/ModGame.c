#include <stdlib.h>
#include <stdio.h>
#include "ModGame.h"

extern void (*Primary_Action)(void);
extern void (*Secondary_Action)(void);

void Game_Primary()
{
	printf("primary action\n");
}
void Game_Secondary()
{
	printf("Secondary action\n");
}

void ModGameInit()
{
	Primary_Action = Game_Primary;
	Secondary_Action = Game_Secondary;
}