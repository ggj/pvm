#ifndef __GAME_H__
#define __GAME_H__

#include <Seed.h>
using namespace Seed;

#include "player.h"
#include "powerup.h"

#include <Box2D/Box2D.h>

class Hud;
class Map;
class MapLayerTiled;
class MapLayerMetadata;
class CollisionObject;
class Baby;

#define GRID_ROW	17
#define GRID_COL	12
#define GRID_SIZE	(GRID_ROW * GRID_COL)

#define SPAWN_INTERVAL 5.0f
#define GLOBAL_PEACE_TIME 180.0f

class Game : public IEventInputKeyboardListener, public IEventInputJoystickListener, public IEventWidgetListener
{
	public:
		Game();
		virtual ~Game();

		void Update(f32 dt);

		BOOL IsFinished() const;
		u32 GetFinishType() const;

		// IEventInputKeyboardListener
		virtual void OnInputKeyboardRelease(const EventInputKeyboard *ev);
		virtual void OnInputKeyboardPress(const EventInputKeyboard *ev);

		// IEventInputJoystickListener
		virtual void OnInputJoystickButtonPress(const EventInputJoystick *ev) const;
		virtual void OnInputJoystickButtonRelease(const EventInputJoystick *ev) const;
		virtual void OnInputJoystickDPadMove(const EventInputJoystick *ev) const;
		virtual void OnInputJoystickAxisMove(const EventInputJoystick *ev) const;

		// IEventWidgetListener
		virtual void OnWidgetPress(const EventWidget *ev);
		virtual void OnWidgetRelease(const EventWidget *ev);
		virtual void OnWidgetReleaseOut(const EventWidget *ev);

	protected:
		b2World *world;

		Hud *pHud;
		Map *pMap;
		MapLayerMetadata *pCollision;

		Player *pPlayer1;
		Player *pPlayer2;

		Player *pPlayerKeyboard1;
		Player *pPlayerKeyboard2;
		Player *pPlayerJoystick1;
		Player *pPlayerJoystick2;

		Baby *pBabyP1;
		Baby *pBabyP2;

		Button btnLeftP1;
		Button btnUpP1;
		Button btnRightP1;

		Button btnLeftP2;
		Button btnUpP2;
		Button btnRightP2;

		f32 fElapsedTime;
		f32 fTimerSpawnBabyP1;
		f32 fTimerSpawnBabyP2;
		f32 fPowerupSpawnTimer;

		u32 iAmountSpawnedP1;
		u32 iAmountSpawnedP2;
		u32 iFinishType;
		mutable u32 iJoystickDpad1;
		mutable u32 iJoystickDpad2;

		BOOL bIsFinished;
		BOOL bPaused;

		Sprite sptBg;
		Sprite sptEnding;
		SoundSource sfxGong;
		Array<PowerUp *, 5> arPowerUps;

	protected:
		void SpawnBaby(eTeam team);
		void SpawnPowerUp();
		void CheckBabyCollision();
		void CheckPowerupCollision();
		void ShowEndingScreen();
		void UsePowerUp(eTeam team, PowerUpType type);

	private:
		CollisionObject *borderTop;
		CollisionObject *borderBottom;
		CollisionObject *borderLeft;
		CollisionObject *borderRight;
};

#endif
