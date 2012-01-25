#ifndef __MAIN_H__
#define __MAIN_H__

#include <Seed.h>
using namespace Seed;

class App;

extern ISceneNode *pScene;
extern ISceneNode *pSceneStatic;
extern App *pApp;

SEED_ENABLE_INSTANCING(Sprite);

#define PRIORITY_BG			(0)
#define PRIORITY_ENTITY		(PRIORITY_BG + 100000)
#define PRIORITY_POWERUP	(PRIORITY_ENTITY + 1)
#define PRIORITY_ENDING		(PRIORITY_POWERUP + 1000)
#define PRIORITY_THANKS		(PRIORITY_ENDING + 1000)
#define PRIORITY_TOUCH		(PRIORITY_THANKS + 10000)
#define PRIORITY_CURSOR		(PRIORITY_TOUCH + 10000)

enum eTeam
{
	TeamPanda,
	TeamMaya,

	MaxTeams
};

enum ePlatformType
{
	TouchDevice,
	PersonalComputer,
	GameConsole
};

extern ePlatformType nPlatform;

void seed_main(int argc, char **argv);

#endif // __MAIN_H__
