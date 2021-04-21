#include "GameScreenLevel1.h"
#include"Texture2D.h"
#include<iostream>
#include"Collisions.h"

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpLevel();
	timer = 2.0f;
	deadLoc.x = -100;
	deadLoc.y = -100;
	//m_level_map = nullptr;

}

GameScreenLevel1::~GameScreenLevel1()
{
	m_background_texture = nullptr;
	delete[] mario;
	delete[] luigi;
	delete[] m_pow_block;
	mario = nullptr; luigi = nullptr; m_pow_block = nullptr;
	m_enemies.clear();
}

void GameScreenLevel1::Render()
{
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

	for (int i = 0; i < m_g_enemies.size(); i++)
	{
		m_g_enemies[i]->Render();
	}

	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render();
	}
	m_background_texture->Render(Vector2D(0,m_background_yPos), SDL_FLIP_NONE);
	if (mario->GetAlive())
	{
		//mario->Render();
		mario->Render();
	}
	luigi->Render();
	m_pow_block->Render();
	if (Collisions::Instances()->Circle(mario->getPosition(), luigi->getPosition(), mario->GetCollisionRadius(),luigi->GetCollisionRadius()))
	{
		std::cout << "circle hit" << std::endl;
	}

	if (Collisions::Instances()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		std::cout << "box hit" << std::endl;
	}
	//my_character->Render();
}

void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}

	}

	//my_character->Update(deltaTime, e);
	if (mario->GetAlive())
	{
		mario->Update(deltaTime, e);
	}
	luigi->Update(deltaTime, e);
	UpdatePowBlock();

	for (int i = 0; i < m_g_enemies.size(); i++)
	{
		m_g_enemies[i]->Update(deltaTime, e);
	}

	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Update(deltaTime, e);
	}
	

	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);
	timer -= deltaTime;
	

	//mario->AddGravity(deltaTime);
}

bool GameScreenLevel1::SetUpLevel()
{
	m_background_texture = new Texture2D(m_renderer);

	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "failed to load background texture!" << std::endl;
		return false;
	}
	//set up character
	SetLevelMap();
	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
	CreateGoomba(Vector2D(150, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateCoins(Vector2D(150, 32));
	mario = new MarioCharacter(m_renderer, "Images/Mario_new.png", Vector2D(64, 330),m_level_map);
	luigi = new LuigiCharacter(m_renderer, "Images/Luigi.png", Vector2D(128, 100),m_level_map);
	m_pow_block = new PowBlock(m_renderer, m_level_map);

	m_screenshake = false;
	m_background_yPos = 0.0f;
	
	//my_character = new Character(m_renderer, "Images/Mario.png", Vector2D(64, 330));
	
	return true;

}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	m_level_map = new LevelMap(map);

}

void GameScreenLevel1::UpdatePowBlock()
{
	if (Collisions::Instances()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailiable())
		{
			if (mario->m_jumping)
			{
				DoScreenshake();
				m_pow_block->TakeHit();
				mario->CancelJump();
			}


		}
	}
	if (Collisions::Instances()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailiable())
		{
			if (luigi->m_jumping)
			{
				DoScreenshake();
				m_pow_block->TakeHit();
				luigi->CancelJump();
			}
		}
	}
}

void GameScreenLevel1::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}

}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (timer <= 0)
	{
		CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_SPEED);
		timer = 2.0f;

	}

	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++ )
		{

			if (m_enemies[i]->getPosition().x >= SCREEN_WIDTH - (m_enemies[i]->GetCollisionBox().width*0.5))
			{
				m_enemies[i]->FlipRightWayUp();
			}
			else if (m_enemies[i]->getPosition().x <= 0)
			{
				m_enemies[i]->FlipRightWayUp();
			}

			if (m_enemies[i]->getPosition().y > 300.0f)
			{
				if (m_enemies[i]->getPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5) || m_enemies[i]->getPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
				{
					m_enemies[i]->SetAlive(false);
				}
			}

			m_enemies[i]->Update(deltaTime, e);
			if ((m_enemies[i]->getPosition().y > 300.0f || m_enemies[i]->getPosition().y <= 64.0f) && (m_enemies[i]->getPosition().x < 64.0f || m_enemies[i]->getPosition().x > SCREEN_WIDTH - 96.0f))
			{

				//m_enemies[i]->FlipRightWayUp();
				//
			}
			else
			{
				if (Collisions::Instances()->Circle(m_enemies[i]->getPosition(), mario->getPosition(), m_enemies[i]->GetCollisionRadius(), mario->GetCollisionRadius()))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else if(m_enemies[i]->getPosition().y + m_enemies[i]->GetCollisionBox().height >=  mario->getPosition().y)
					{
						m_enemies[i]->TakeDamage();

					}
					else
					{
						mario->SetAlive(false);//to kill the big fat man
						mario->setPosition(deadLoc);
					}
				}
			}

			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;

			}
		}

		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);

		}
	
	}


}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed);
	m_enemies.push_back(koopa);

}

void GameScreenLevel1::CreateGoomba(Vector2D position, FACING direction, float speed)
{
	goomba = new CharacterGoomba(m_renderer, "Images/Goomba.png", position, m_level_map, direction, speed);
	m_g_enemies.push_back(goomba);
}

void GameScreenLevel1::CreateCoins(Vector2D position)
{
	m_coin = new CharacterCoin(m_renderer, "Images/Coin.png", position, m_level_map);
	m_coins.push_back(m_coin);
}

void GameScreenLevel1::UpdateCoins(float deltaTime, SDL_Event e)
{
	if (!m_coins.empty())
	{
		int CoinToDelete = -1;
		for (unsigned int i = 0; i < m_coins.size(); i++)
		{
			if (!m_coins[i]->GetCollected())
			{
				if (Collisions::Instances()->Circle(m_coins[i]->getPosition(), mario->getPosition(), m_coins[i]->GetCollisionRadius(), mario->GetCollisionRadius()))
				{
					
					m_coins[i]->SetCollect(true);
					CoinToDelete = i;
					
				}
				if (Collisions::Instances()->Circle(m_coins[i]->getPosition(), luigi->getPosition(), m_coins[i]->GetCollisionRadius(), luigi->GetCollisionRadius()))
				{
					m_coins[i]->SetCollect(true);
					CoinToDelete = i;
				}
			}

			if (CoinToDelete != -1)
			{
				m_coins.erase(m_coins.begin() + CoinToDelete);
			}
		}
	}
}

void GameScreenLevel1::RenderText()
{
	

}