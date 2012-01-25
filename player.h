#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "main.h"
#include "actor.h"

#define PLAYER_LIFES	5
#define RESPAWN_TIME	2.5f

enum AnimationState
{
	ATTACK = 0,
	DEATH,
	FALL,
	FLY_UP,
	FLY_DOWN,
	IDLE,
	RUN
};

class MapLayerMetadata;

class Player : public Actor
{
	public:
		Player(b2World *world, eTeam team);
		virtual ~Player();

		virtual void Update(f32 dt, MapLayerMetadata *collision, Player *player);
		virtual eTeam GetTeam() const;

		virtual void StartThrust();
		virtual void StopThrust();
		virtual void StartRight();
		virtual void StopRight();
		virtual void StartLeft();
		virtual void StopLeft();

		virtual void IncLife();
		virtual void DecLife();
		virtual u32 GetLife();

		virtual void Hit(Player *player);

	public:
		Sprite sptShield;
		Sprite sptWeight;

		AnimationState eAnimation;

		f32 fElapsedDeathTime;
		f32 fElapsedInvertTime;
		f32 fElapsedGravityTime;
		f32 fElapsedWeightTime;
		f32 fElapsedShieldTime;

		BOOL bReducedGravity;
		BOOL bEnableShield;
		BOOL bLockControls;

	protected:
		virtual void ResolveCollision(MapLayerMetadata *pCollision, Player *player);
		virtual void ResolveAnimation();
		virtual void SetAnimation(AnimationState eAnimation);
		virtual void StopAllSounds();

	protected:
		eTeam nTeam;

		u32 iLives;

		SoundSource sfxThrust;
		SoundSource sfxThrustFail;
		SoundSource sfxDeath;
		SoundSource sfxHit;
		SoundSource sfxSteps;
};

#endif // __PLAYER_H__
