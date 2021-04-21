#pragma once
#ifndef _GameScreenLevel1_h
#define _GameScreenLevel1_h

#include"commons.h"
#include"GameScreen.h"
#include<SDL.h>
#include"Character.h"
#include"MarioCharacter.h"
#include"LuigiCharacter.h"
#include"PowBlock.h"
#include"LevelMap.h"
#include"Collisions.h"
#include"CharacterKoopa.h"
#include"CharacterGoomba.h"
#include"CharacterCoin.h"
#include<vector>
class Texture2D;

class Character;

class MarioCharacter;

class LuigiCharacter;

class PowBlock;

class GameScreenLevel1 : GameScreen
{
private:
	Texture2D* m_background_texture;
	Character* my_character;
	MarioCharacter* mario;
	LuigiCharacter* luigi;
	CharacterKoopa* koopa;
	CharacterGoomba* goomba;
	PowBlock* m_pow_block;
	CharacterCoin* m_coin;
	void SetLevelMap();
	LevelMap* m_level_map;
	Vector2D deadLoc;
	bool SetUpLevel();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void UpdateCoins(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateCoins(Vector2D position);
	void CreateGoomba(Vector2D position, FACING direction, float speed);
	float timer;
	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	
	std::vector<CharacterKoopa*> m_enemies;
	std::vector<CharacterGoomba*> m_g_enemies;
	std::vector<CharacterCoin*> m_coins;

	void DoScreenshake();

public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	void UpdatePowBlock();

	void RenderText();

};

#endif // !_GameScreenLevel1_h