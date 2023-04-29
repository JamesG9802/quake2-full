#pragma once

/*	Hard coded Pixel Coordinates	*/
#define MOD_WINDOW_WIDTH	800
#define MOD_WINDOW_HEIGHT	600

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

#define MOD_PROJECTILE_PNG_WIDTH 28
#define MOD_PROJECTILE_PNG_HEIGHT 28

#define MOD_PROJECTILE0_PNG_WIDTH 28
#define MOD_PROJECTILE0_PNG_HEIGHT 28

#define MOD_PROJECTILE1_PNG_WIDTH 28
#define MOD_PROJECTILE1_PNG_HEIGHT 28

/*	Game Information	*/
#define MOD_GRID_ROWS 5
#define MOD_GRID_COLS 9

#define MOD_GAME_INITSUN	50
#define MOD_GAME_SUNVALUE	25

#define MOD_SUNFLOWER	0
#define MOD_PEASHOOTER	1
#define MOD_WALLNUT	2
#define MOD_CHERRYBOMB	3
#define MOD_JALEPENO	4
#define MOD_EXPLODENUT	5
#define MOD_REPEATER	6
#define MOD_TORCHWOOD	7
#define MOD_MOUSESHOOTER	8
#define MOD_CHOMPER	9

#define MOD_LOWEST_PLANT_INDEX	MOD_SUNFLOWER
#define	MOD_HIGHEST_PLANT_INDEX	MOD_CHOMPER

#define MOD_SUNFLOWER_COST	50
#define MOD_PEASHOOTER_COST	100
#define MOD_WALLNUT_COST	50
#define MOD_CHERRYBOMB_COST	150
#define MOD_JALEPENO_COST	125
#define MOD_EXPLODENUT_COST	75
#define MOD_REPEATER_COST	200
#define MOD_TORCHWOOD_COST	175
#define MOD_MOUSESHOOTER_COST	75
#define MOD_CHOMPER_COST	150

#define MOD_PLANT_HEALTH_NORMAL	300
#define MOD_PLANT_HEALTH_HIGH	4000

#define MOD_DAMAGE_INSTANTKILL	4000	


#define MOD_PLANT_DAMAGE_NORMAL 20

#define MOD_SUNFLOWER_COOLDOWN	8	//	24 seconds in reality
#define MOD_PEASHOOTER_COOLDOWN	1.5
#define MOD_CHERRYBOMB_COOLDOWN	1
#define MOD_JALEPENO_COOLDOWN	1
#define MOD_REPEATER_COOLDOWN	1.5
#define MOD_MOUSESHOOTER_COOLDOWN 2.0/3.0
#define MOD_CHOMPER_COOLDOWN	20

#define MOD_ZOMBIE_REGULAR	0
#define MOD_ZOMBIE_CONE	1
#define MOD_ZOMBIE_BUCKET	2
#define MOD_ZOMBIE_FLAG	3
#define MOD_ZOMBIE_FOOTBALL	4

#define MOD_ZOMBIE_HEALTH_LOW	180
#define MOD_ZOMBIE_HEALTH_NORMAL	MOD_ZOMBIE_HEALTH_LOW * 2
#define MOD_ZOMBIE_HEALTH_HIGH	MOD_ZOMBIE_HEALTH_LOW * 3

#define MOD_ZOMBIE_DAMAGE_NORMAL 100

#define MOD_ZOMBIE_SPEED_NORMAL	1/4.7	// grid width per seconds
#define MOD_ZOMBIE_SPEED_HIGH	2/4.7	// grid width per seconds

#define MOD_PROJECTILE_SPEED_NORMAL	4	//	grid width per seconds

/*	Class Information	*/
#define MOD_CLASS_ZOMBIE	"zombie"
#define MOD_CLASS_PROJECTILE	"projectile"
/*	Pictures	*/

#define MOD_BACKGROUND_PNG	"pics/lawn.png"
#define MOD_GRIDGLOW_PNG	"pics/gridglow.png"

#define	MOD_SUNFLOWER_PNG	"pics/plant0.png"
#define	MOD_PEASHOOTER_PNG	"pics/plant1.png"
#define MOD_WALLNUT_PNG	"pics/plant2.png"
#define MOD_CHERRYBOMB_PNG	"pics/plant3.png"
#define MOD_JALEPENO_PNG	"pics/plant4.png"
#define MOD_EXPLODENUT_PNG	"pics/plant5.png"
#define MOD_REPEATER_PNG	"pics/plant6.png"
#define MOD_TORCHWOOD_PNG	"pics/plant7.png"
#define MOD_MOUSESHOOTER_PNG	"pics/plant8.png"
#define MOD_CHOMPER_PNG	"pics/plant9.png"

#define MOD_SUN_PNG			"pics/sun.png"

#define MOD_ZOMBIE_REGULAR_PNG	"pics/zombie0.png"
#define MOD_ZOMBIE_CONE_PNG	"pics/zombie1.png"
#define MOD_ZOMBIE_BUCKET_PNG	"pics/zombie2.png"
#define MOD_ZOMBIE_FLAG_PNG	"pics/zombie3.png"
#define MOD_ZOMBIE_FOOTBALL_PNG	"pics/zombie4.png"

#define MOD_PEA_PNG	"pics/proj0.png"
#define MOD_FIREPEA_PNG	"pics/proj1.png"
/*	Fonts	*/
#define MOD_TEXT_TTF		"fonts/cour.ttf"
#define MOD_TEXTBOLD_TTF	"fonts/courbd.ttf"