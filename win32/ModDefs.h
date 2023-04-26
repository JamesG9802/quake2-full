#pragma once

/*	Hard coded Pixel Coordinates	*/
#define MOD_BACKGROUND_XOFFSET -200
#define MOD_GRID_XPOS 50
#define MOD_GRID_YPOS 80
#define MOD_GRID_WIDTH 80
#define MOD_GRID_HEIGHT 97

#define MOD_GRIDGLOW_PNG_WIDTH	256
#define MOD_GRIDGLOW_PNG_HEIGHT	256

#define MOD_SUNUI_PNG_WIDTH	256
#define MOD_SUNUI_PNG_HEIGHT	256

#define MOD_PLANT_PNG_WIDTH		96
#define	MOD_PLANT_PNG_HEIGHT	96

#define MOD_ZOMBIE_PNG_WIDTH	96
#define MOD_ZOMBIE_PNG_HEIGHT	96

#define MOD_SUN_WIDTH 64
#define MOD_SUN_HEIGHT 64

#define	MOD_SUN_PNG_WIDTH 145
#define MOD_SUN_PNG_HEIGHT 149

#define MOD_PROJECTILE_PNG_WIDTH 32
#define MOD_PROJECTILE_PNG_HEIGHT 32

#define MOD_PROJECTILE0_PNG_WIDTH 64
#define MOD_PROJECTILE0_PNG_HEIGHT 60

/*	Game Information	*/
#define MOD_GRID_ROWS 5
#define MOD_GRID_COLS 9

#define MOD_GAME_INITSUN	50
#define MOD_GAME_SUNVALUE	25

#define MOD_SUNFLOWER	0
#define MOD_PEASHOOTER	1

#define MOD_PLANT_HEALTH_NORMAL	300

#define MOD_PLANT_DAMAGE_NORMAL 150

#define MOD_SUNFLOWER_COOLDOWN	5	//	24 seconds in reality
#define MOD_PEASHOOTER_COOLDOWN	1.5

#define MOD_ZOMBIE_REGULAR	0

#define MOD_ZOMBIE_HEALTH_LOW	180

#define MOD_ZOMBIE_DAMAGE_NORMAL 100

#define MOD_ZOMBIE_SPEED_NORMAL	1/4.7	// grid width per seconds

#define MOD_PROJECTILE_SPEED_NORMAL	4	//	grid width per seconds

/*	Class Information	*/
#define MOD_CLASS_ZOMBIE	"zombie"

/*	Pictures	*/

#define MOD_BACKGROUND_PNG	"pics/lawn.png"
#define MOD_GRIDGLOW_PNG	"pics/gridglow.png"

#define	MOD_SUNFLOWER_PNG	"pics/plant0.png"
#define	MOD_PEASHOOTER_PNG	"pics/plant1.png"
#define MOD_SUN_PNG			"pics/sun.png"

#define MOD_ZOMBIE_REGULAR_PNG	"pics/zombie0.png"

#define MOD_PEA_PNG	"pics/proj0.png"
/*	Fonts	*/
#define MOD_TEXT_TTF		"fonts/cour.ttf"
#define MOD_TEXTBOLD_TTF	"fonts/courbd.ttf"