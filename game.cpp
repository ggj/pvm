#include "main.h"
#include "app.h"
#include "game.h"
#include "map.h"
#include "maplayertiled.h"
#include "maplayermetadata.h"
#include "collisionobject.h"
#include "assets.h"
#include "hud.h"
#include "baby.h"
#include "powerup.h"
#include <time.h>

#define BTN_LEFT_P1		1
#define BTN_RIGHT_P1	2
#define BTN_UP_P1		3
#define BTN_LEFT_P2		4
#define BTN_RIGHT_P2	5
#define BTN_UP_P2		6

Game::Game()
	: pHud(NULL)
	, pMap(NULL)
	, pCollision(NULL)
	, pPlayer1(NULL)
	, pPlayer2(NULL)
	, pPlayerKeyboard1(NULL)
	, pPlayerKeyboard2(NULL)
	, pPlayerJoystick1(NULL)
	, pPlayerJoystick2(NULL)
	, pBabyP1(NULL)
	, pBabyP2(NULL)
	, fElapsedTime(0.0f)
	, fTimerSpawnBabyP1(0.0f)
	, fTimerSpawnBabyP2(0.0f)
	, fPowerupSpawnTimer(0.0f)
	, iAmountSpawnedP1(0)
	, iAmountSpawnedP2(0)
	, iFinishType(0)
	, iJoystickDpad1(0)
	, iJoystickDpad2(0)
	, bIsFinished(FALSE)
	, bPaused(FALSE)
{
	pHud = New(Hud());

	if (nPlatform == TouchDevice)
	{
		btnLeftP1.Initialize(BTN_LEFT_P1);
		btnLeftP1.SetSprite(SPT_LR);
		btnLeftP1.SetPosition(0.02f, 0.9f);
		btnLeftP1.SetPriority(PRIORITY_TOUCH);
		btnLeftP1.SetSpriteColor(1.0f, 1.0f, 1.0f, 0.5f);
		btnLeftP1.SetSpriteBlending(Seed::BlendModulate);
		btnLeftP1.AddListener(this);
		pGuiManager->Add(&btnLeftP1);
		pScene->Add(&btnLeftP1);

		btnRightP1.Initialize(BTN_RIGHT_P1);
		btnRightP1.SetSprite(SPT_LR);
		btnRightP1.SetPosition(0.08f, 0.9f);
		btnRightP1.SetPriority(PRIORITY_TOUCH);
		btnRightP1.SetSpriteColor(1.0f, 1.0f, 1.0f, 0.5f);
		btnRightP1.SetSpriteBlending(Seed::BlendModulate);
		btnRightP1.AddListener(this);
		pGuiManager->Add(&btnRightP1);
		pScene->Add(&btnRightP1);

		btnUpP1.Initialize(BTN_UP_P1);
		btnUpP1.SetSprite(SPT_UP);
		btnUpP1.SetPosition(0.053f, 0.88f);
		btnUpP1.SetPriority(PRIORITY_TOUCH + 1);
		btnUpP1.SetSpriteColor(1.0f, 1.0f, 1.0f, 0.5f);
		btnUpP1.SetSpriteBlending(Seed::BlendModulate);
		btnUpP1.AddListener(this);
		pGuiManager->Add(&btnUpP1);
		pScene->Add(&btnUpP1);

		btnLeftP2.Initialize(BTN_LEFT_P2);
		btnLeftP2.SetSprite(SPT_LR);
		btnLeftP2.SetPosition(0.86f, 0.9f);
		btnLeftP2.SetPriority(PRIORITY_TOUCH);
		btnLeftP2.SetSpriteColor(1.0f, 1.0f, 1.0f, 0.5f);
		btnLeftP2.SetSpriteBlending(Seed::BlendModulate);
		btnLeftP2.AddListener(this);
		pGuiManager->Add(&btnLeftP2);
		pScene->Add(&btnLeftP2);

		btnRightP2.Initialize(BTN_RIGHT_P2);
		btnRightP2.SetSprite(SPT_LR);
		btnRightP2.SetPosition(0.92f, 0.9f);
		btnRightP2.SetPriority(PRIORITY_TOUCH);
		btnRightP2.SetSpriteColor(1.0f, 1.0f, 1.0f, 0.5f);
		btnRightP2.SetSpriteBlending(Seed::BlendModulate);
		btnRightP2.AddListener(this);
		pGuiManager->Add(&btnRightP2);
		pScene->Add(&btnRightP2);

		btnUpP2.Initialize(BTN_UP_P2);
		btnUpP2.SetSprite(SPT_UP);
		btnUpP2.SetPosition(0.893f, 0.88f);
		btnUpP2.SetPriority(PRIORITY_TOUCH + 1);
		btnUpP2.SetSpriteColor(1.0f, 1.0f, 1.0f, 0.5f);
		btnUpP2.SetSpriteBlending(Seed::BlendModulate);
		btnUpP2.AddListener(this);
		pGuiManager->Add(&btnUpP2);
		pScene->Add(&btnUpP2);
	}

//BOX2D ***********************************
	b2Vec2 gravity(0.0f, -10.0f);
	world = New(b2World(gravity, true));
// ****************************************

	pInput->AddKeyboardListener(this);
	pInput->AddJoystickListener(this);

	sptBg.Load(SPT_BG);
	sptBg.SetPriority(PRIORITY_BG);
	pScene->Add(&sptBg);

	pMap = New(Map(world));
	pMap->SetWidth(1.0f);
	pMap->SetHeight(1.0f);
	pMap->SetPriority(5);

	u32 map = clock() % 5;
	pMap->Load(_F(map + MAP_LV1_ID));
	pMap->SetPriority(PRIORITY_BG + 1);

	MapLayerTiled *bg = pMap->GetLayerAt(0)->AsTiled();
	if (bg)
	{
		bg->SetTileSet(SPT_TILESET_TILESET01);
	}
	pCollision = pMap->GetLayerAt(1)->AsMetadata();
	pScene->Add(pMap);

	pPlayer1 = New(Player(world, TeamPanda));
	pPlayer2 = New(Player(world, TeamMaya));
	pPlayer2->GetSprite().SetPosition(1.0f, 0.0f);

	pHud->SetFirstPlayerLifes(pPlayer1->GetLife());
	pHud->SetSecondPlayerLifes(pPlayer2->GetLife());

	sptEnding.Load(SPT_GAMEOVER_PANDA);
	sptEnding.SetPriority(PRIORITY_ENDING);
	sptEnding.SetVisible(FALSE);
	pScene->Add(&sptEnding);

	sfxGong.Load(SFX_START_FIGHT);
	//sfxGong.SetVolume(0.5f);
	pSoundSystem->Add(&sfxGong);
	sfxGong.Play();

	this->SpawnBaby(TeamPanda);
	this->SpawnBaby(TeamMaya);

	f32 size = 4.0f;

	borderTop = New(CollisionObject(world));
	borderTop->SetPosition(0.0f, size);
	borderTop->SetWidth(static_cast<f32>(pScreen->GetWidth()));
	borderTop->SetHeight(size);
	borderTop->CreateStaticBody(borderTop->GetX(), borderTop->GetY(), borderTop->GetWidth(), borderTop->GetHeight());
	pScene->Add(borderTop);

	borderBottom = New(CollisionObject(world));
	borderBottom->SetPosition(0.0f, static_cast<f32>(pScreen->GetHeight()));
	borderBottom->SetWidth(static_cast<f32>(pScreen->GetWidth()));
	borderBottom->SetHeight(size);
	borderBottom->CreateStaticBody(borderBottom->GetX(), borderBottom->GetY(), borderBottom->GetWidth(), borderBottom->GetHeight());
	pScene->Add(borderBottom);

	borderLeft = New(CollisionObject(world));
	borderLeft->SetPosition(0.0f, static_cast<f32>(pScreen->GetHeight()));
	borderLeft->SetWidth(size);
	borderLeft->SetHeight(static_cast<f32>(pScreen->GetHeight()));
	borderLeft->CreateStaticBody(borderLeft->GetX(), borderLeft->GetY(), borderLeft->GetWidth(), borderLeft->GetHeight());
	pScene->Add(borderLeft);

	borderRight = New(CollisionObject(world));
	borderRight->SetPosition(static_cast<f32>(pScreen->GetWidth()) - size, static_cast<f32>(pScreen->GetHeight()));
	borderRight->SetWidth(size);
	borderRight->SetHeight(static_cast<f32>(pScreen->GetHeight()));
	borderRight->CreateStaticBody(borderRight->GetX(), borderRight->GetY(), borderRight->GetWidth(), borderRight->GetHeight());
	pScene->Add(borderRight);

	switch (pApp->GetControlType())
	{
		case Keyboard1Joystick1:
		{
			pPlayerKeyboard1 = pPlayer1;
			pPlayerKeyboard2 = NULL;
			pPlayerJoystick1 = pPlayer2;
			pPlayerJoystick2 = NULL;
		}
		break;

		case Joystick1Keyboard2:
		{
			pPlayerKeyboard1 = NULL;
			pPlayerKeyboard2 = pPlayer2;
			pPlayerJoystick1 = pPlayer1;
			pPlayerJoystick2 = NULL;
		}
		break;

		case Joystick1Joystick2:
		{
			pPlayerKeyboard1 = NULL;
			pPlayerKeyboard2 = NULL;
			pPlayerJoystick1 = pPlayer1;
			pPlayerJoystick2 = pPlayer2;
		}
		break;

		default:
		case Keyboard1Keyboard2:
		{
			pPlayerKeyboard1 = pPlayer1;
			pPlayerKeyboard2 = pPlayer2;
			pPlayerJoystick1 = NULL;
			pPlayerJoystick2 = NULL;
		}
		break;
	}
}

Game::~Game()
{
	pScene->Reset();

	pInput->RemoveJoystickListener(this);
	pInput->RemoveKeyboardListener(this);

	Delete(pMap);
	Delete(pPlayer1);
	Delete(pPlayer2);

	if (pBabyP1)
	{
		Delete(pBabyP1);
		pBabyP1 = NULL;
	}

	if (pBabyP2)
	{
		Delete(pBabyP2);
		pBabyP2 = NULL;
	}

	Delete(pHud);
	pHud = NULL;

	Delete(borderTop);
	Delete(borderBottom);
	Delete(borderLeft);
	Delete(borderRight);

	Delete(world);
	world = NULL;
}

void Game::Update(f32 dt)
{
	if (bPaused)
		return;

	fElapsedTime += dt;

	world->Step(dt, 6, 2);
	world->ClearForces();

	pPlayer1->Update(dt, pCollision, pPlayer2);
	pPlayer2->Update(dt, pCollision, pPlayer1);

	if (pBabyP1)
		pBabyP1->Update(dt, pCollision);

	if (pBabyP2)
		pBabyP2->Update(dt, pCollision);

	for (u32 i = 0; i < arPowerUps.Size(); i++)
	{
		arPowerUps[i]->Update(dt, pCollision);
	}

	this->CheckBabyCollision();
	this->CheckPowerupCollision();

	pHud->SetFirstPlayerLifes(pPlayer1->GetLife());
	pHud->SetSecondPlayerLifes(pPlayer2->GetLife());

	if (!pBabyP1 && pPlayer1->GetLife() < 10 && iAmountSpawnedP1 <= 5)
	{
		fTimerSpawnBabyP1 += dt;
		if (fTimerSpawnBabyP1 >= SPAWN_INTERVAL)
			this->SpawnBaby(TeamPanda);
	}

	if (!pBabyP2 && pPlayer2->GetLife() < 10 && iAmountSpawnedP2 <= 5)
	{
		fTimerSpawnBabyP2 += dt;
		if (fTimerSpawnBabyP2 >= SPAWN_INTERVAL)
			this->SpawnBaby(TeamMaya);
	}

	if (pPlayer1->GetLife() <= 0)
	{
		iFinishType = 0;
		bPaused = TRUE;
	}
	else if (pPlayer2->GetLife() <= 0)
	{
		iFinishType = 1;
		bPaused = TRUE;
	}
	else if (fElapsedTime > GLOBAL_PEACE_TIME)
	{
		iFinishType = 2;
		bPaused = TRUE;
	}

	if (arPowerUps.Size() < 5)
	{
		fPowerupSpawnTimer += dt;
		if (fPowerupSpawnTimer > 5.0f)
		{
			fPowerupSpawnTimer -= 5.0f;

			this->SpawnPowerUp();
		}
	}

	if (bPaused)
		this->ShowEndingScreen();
}

BOOL Game::IsFinished() const
{
	return bIsFinished;
}

u32 Game::GetFinishType() const
{
	return iFinishType;
}

void Game::ShowEndingScreen()
{
	sptEnding.SetAnimation((u32)iFinishType);
	sptEnding.SetVisible(TRUE);
}

void Game::CheckPowerupCollision()
{
	Rect4f overlap;

	BOOL collide = TRUE;
	for (s32 i = arPowerUps.Size() - 1; i >= 0; i--)
	{
		collide = pPlayer1->CheckHit(arPowerUps[i]->GetBoundingBox(), overlap);
		if (collide)
		{
			this->UsePowerUp(TeamPanda, arPowerUps[i]->GetType());
			Delete(arPowerUps[i]);
			arPowerUps.Del(i);

			continue;
		}

		collide = pPlayer2->CheckHit(arPowerUps[i]->GetBoundingBox(), overlap);
		if (collide)
		{
			this->UsePowerUp(TeamMaya, arPowerUps[i]->GetType());
			Delete(arPowerUps[i]);
			arPowerUps.Del(i);
		}
	}
}

void Game::UsePowerUp(eTeam team, PowerUpType type)
{
	switch (team)
	{
		case TeamPanda:
		{
			switch (type)
			{
				case PU_CONTROL:
				{
					pPlayer2->SetInvertedAxis(TRUE);
					pPlayer2->fElapsedInvertTime	= 0;
				}
				break;

				case PU_GRAVITY:
				{
					pPlayer1->bReducedGravity		= TRUE;
					pPlayer1->SetGravityModifier(0.25f);
					pPlayer1->fElapsedGravityTime	= 0;
				}
				break;

				case PU_SHIELD:
				{
					pPlayer1->sptShield.SetVisible(TRUE);
					pPlayer1->bEnableShield			= TRUE;
					pPlayer1->fElapsedShieldTime	= 0;
				}
				break;

				case PU_WEIGHT:
				{
					pPlayer2->sptWeight.SetVisible(TRUE);
					pPlayer2->SetHeavy(TRUE);
					pPlayer2->fElapsedWeightTime	= 0;
					pPlayer2->SetGravityModifier(-0.15f);
				}
				break;

				default:
				break;
			}
		}
		break;

		case TeamMaya:
		{
			switch (type)
			{
				case PU_CONTROL:
				{
					pPlayer1->SetInvertedAxis(TRUE);
					pPlayer1->fElapsedInvertTime	= 0;
				}
				break;

				case PU_GRAVITY:
				{
					pPlayer2->bReducedGravity		= TRUE;
					pPlayer2->SetGravityModifier(0.25f);
					pPlayer2->fElapsedGravityTime	= 0;
				}
				break;

				case PU_SHIELD:
				{
					pPlayer2->sptShield.SetVisible(TRUE);
					pPlayer2->bEnableShield			= TRUE;
					pPlayer2->fElapsedShieldTime	= 0;
				}
				break;

				case PU_WEIGHT:
				{
					pPlayer1->sptWeight.SetVisible(TRUE);
					pPlayer1->SetHeavy(TRUE);
					pPlayer1->fElapsedWeightTime	= 0;
					pPlayer1->SetGravityModifier(-0.15f);
				}
				break;

				default:
				break;
			}
		}
		break;

		default:
		break;
	}
}

void Game::CheckBabyCollision()
{
	Rect4f overlap;

	if (pBabyP2 && pPlayer1->CheckHit(pBabyP2->GetBoundingBox(), overlap))
	{
		Delete(pBabyP2);
		pBabyP2 = NULL;

		fTimerSpawnBabyP2 = 0;
	}

	if (pBabyP1 && pPlayer1->CheckHit(pBabyP1->GetBoundingBox(), overlap))
	{
		Delete(pBabyP1);
		pBabyP1 = NULL;

		pPlayer1->IncLife();

		fTimerSpawnBabyP1 = 0;
	}

	if (pBabyP1 && pPlayer2->CheckHit(pBabyP1->GetBoundingBox(), overlap))
	{
		Delete(pBabyP1);
		pBabyP1 = NULL;

		fTimerSpawnBabyP1 = 0;
	}

	if (pBabyP2 && pPlayer2->CheckHit(pBabyP2->GetBoundingBox(), overlap))
	{
		Delete(pBabyP2);
		pBabyP2 = NULL;

		pPlayer2->IncLife();

		fTimerSpawnBabyP2 = 0;
	}
}

void Game::SpawnPowerUp()
{
	u32 iType = pRand->Get((u32)4);
	PowerUpType eType;
	switch (iType)
	{
		case 0:
		{
			eType = PU_WEIGHT;
		}
		break;

		case 1:
		{
			eType = PU_GRAVITY;
		}
		break;

		case 2:
		{
			eType = PU_CONTROL;
		}
		break;

		case 3:
		{
			eType = PU_SHIELD;
		}
		break;

		default:
		break;
	}

	PowerUp *pPowerUp = New(PowerUp(world, eType));
	pPowerUp->GetSprite().SetPosition(pRand->Get(1.0f), pRand->Get(1.0f));
	pPowerUp->CreateDinamycBody(pPowerUp->GetSprite().GetX(), pPowerUp->GetSprite().GetY(), pPowerUp->GetSprite().GetWidth(), pPowerUp->GetSprite().GetHeight(), COLLISION_OBJECT, COLLISION_GROUND | COLLISION_OBJECT);

	arPowerUps.Add(pPowerUp);
}

void Game::SpawnBaby(eTeam team)
{
	if (team == TeamPanda)
	{
		pBabyP1 = New(Baby(world));
		pBabyP1->Load(TeamPanda);
		pBabyP1->GetSprite().SetPosition(pRand->Get(1.0f), pRand->Get(1.0f));
		pBabyP1->CreateDinamycBody(pBabyP1->GetSprite().GetX(), pBabyP1->GetSprite().GetY(), pBabyP1->GetSprite().GetWidth(), pBabyP1->GetSprite().GetHeight(), COLLISION_OBJECT, COLLISION_GROUND | COLLISION_OBJECT);

		iAmountSpawnedP1++;
	}
	else
	{
		pBabyP2 = New(Baby(world));
		pBabyP2->Load(TeamMaya);
		pBabyP2->GetSprite().SetPosition(pRand->Get(1.0f), pRand->Get(1.0f));
		pBabyP2->CreateDinamycBody(pBabyP2->GetSprite().GetX(), pBabyP2->GetSprite().GetY(), pBabyP2->GetSprite().GetWidth(), pBabyP2->GetSprite().GetHeight(), COLLISION_OBJECT, COLLISION_GROUND | COLLISION_OBJECT);

		iAmountSpawnedP2++;
	}
}

void Game::OnInputKeyboardPress(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (pPlayerKeyboard2)
	{
		switch (k.GetValue())
		{
			case Seed::KeyUp:
			{
				pPlayerKeyboard2->StartThrust();
			}
			break;

			case Seed::KeyLeft:
			{
				pPlayerKeyboard2->StartLeft();
			}
			break;

			case Seed::KeyRight:
			{
				pPlayerKeyboard2->StartRight();
			}
			break;
		}
	}

	if (pPlayerKeyboard1)
	{
		switch (k.GetValue())
		{
			case Seed::KeyW:
			case 'w':
			{
				pPlayerKeyboard1->StartThrust();
			}
			break;

			case Seed::KeyA:
			case 'a':
			{
				pPlayerKeyboard1->StartLeft();
			}
			break;

			case Seed::KeyD:
			case 'd':
			{
				pPlayerKeyboard1->StartRight();
			}
			break;
		}
	}

	if (k.GetValue() == Seed::KeyReturn)
	{
		if (bPaused)
		{
			bIsFinished = TRUE;
		}
	}
}

void Game::OnInputKeyboardRelease(const EventInputKeyboard *ev)
{
	Key k = ev->GetKey();

	if (pPlayerKeyboard2)
	{
		switch (k.GetValue())
		{
			case Seed::KeyUp:
			{
				pPlayerKeyboard2->StopThrust();
			}
			break;

			case Seed::KeyLeft:
			{
				pPlayerKeyboard2->StopLeft();
			}
			break;

			case Seed::KeyRight:
			{
				pPlayerKeyboard2->StopRight();
			}
			break;
		}
	}

	if (pPlayerKeyboard1)
	{
		switch (k.GetValue())
		{
			case Seed::KeyW:
			case 'w':
			{
				pPlayerKeyboard1->StopThrust();
			}
			break;

			case Seed::KeyA:
			case 'a':
			{
				pPlayerKeyboard1->StopLeft();
			}
			break;

			case Seed::KeyD:
			case 'd':
			{
				pPlayerKeyboard1->StopRight();
			}
			break;
		}
	}
}

void Game::OnInputJoystickButtonPress(const EventInputJoystick *ev) const
{
}

void Game::OnInputJoystickButtonRelease(const EventInputJoystick *ev) const
{
}

void Game::OnInputJoystickDPadMove(const EventInputJoystick *ev) const
{
	if (pPlayerJoystick1)
	{
		u32 oldState = iJoystickDpad1;
		iJoystickDpad1 = ev->GetValue();

		u32 diff = oldState ^ iJoystickDpad1;

		u32 up = diff & 1;
		if (up)
		{
			u32 oldUp = oldState & 1;

			if (!oldUp)
				pPlayerJoystick1->StartThrust();
			else
				pPlayerJoystick1->StopThrust();
		}

		u32 left = diff & 8;
		if (left)
		{
			u32 oldLeft = oldState & 8;
			if (!oldLeft)
				pPlayerJoystick1->StartLeft();
			else
				pPlayerJoystick1->StopLeft();
		}

		u32 right = diff & 2;
		if (right)
		{
			u32 oldRight = oldState & 2;
			if (!oldRight)
				pPlayerJoystick1->StartRight();
			else
				pPlayerJoystick1->StopRight();
		}
	}

	if (pPlayerJoystick2 && ev->GetJoystick() == 1)
	{
		u32 oldState = iJoystickDpad2;
		iJoystickDpad2 = ev->GetValue();

		u32 diff = oldState ^ iJoystickDpad2;

		u32 up = diff & 1;
		if (up)
		{
			u32 oldUp = oldState & 1;

			if (!oldUp)
				pPlayerJoystick2->StartThrust();
			else
				pPlayerJoystick2->StopThrust();
		}

		u32 left = diff & 8;
		if (left)
		{
			u32 oldLeft = oldState & 8;
			if (!oldLeft)
				pPlayerJoystick2->StartLeft();
			else
				pPlayerJoystick2->StopLeft();
		}

		u32 right = diff & 2;
		if (right)
		{
			u32 oldRight = oldState & 2;
			if (!oldRight)
				pPlayerJoystick2->StartRight();
			else
				pPlayerJoystick2->StopRight();
		}
	}
}

void Game::OnInputJoystickAxisMove(const EventInputJoystick *ev) const
{
	if (pPlayerJoystick1)
	{
	}

	if (pPlayerJoystick2 && ev->GetJoystick() == 1)
	{
	}
}

void Game::OnWidgetPress(const EventWidget *ev)
{
	switch (ev->GetSender()->GetId())
	{
		case BTN_LEFT_P1:
		{
			pPlayer1->StartLeft();
		}
		break;

		case BTN_RIGHT_P1:
		{
			pPlayer1->StartRight();
		}
		break;

		case BTN_UP_P1:
		{
			pPlayer1->StartThrust();
		}
		break;

		case BTN_LEFT_P2:
		{
			pPlayer2->StartLeft();
		}
		break;

		case BTN_RIGHT_P2:
		{
			pPlayer2->StartRight();
		}
		break;

		case BTN_UP_P2:
		{
			pPlayer2->StartThrust();
		}
		break;
	}
}

void Game::OnWidgetReleaseOut(const EventWidget *ev)
{
	this->OnWidgetRelease(ev);
}

void Game::OnWidgetRelease(const EventWidget *ev)
{
	switch (ev->GetSender()->GetId())
	{
		case BTN_LEFT_P1:
		{
			pPlayer1->StopLeft();
		}
		break;

		case BTN_RIGHT_P1:
		{
			pPlayer1->StopRight();
		}
		break;

		case BTN_UP_P1:
		{
			pPlayer1->StopThrust();
		}
		break;

		case BTN_LEFT_P2:
		{
			pPlayer2->StopLeft();
		}
		break;

		case BTN_RIGHT_P2:
		{
			pPlayer2->StopRight();
		}
		break;

		case BTN_UP_P2:
		{
			pPlayer2->StopThrust();
		}
		break;
	}
}
