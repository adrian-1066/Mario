#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, Vector2D startPosition, LevelMap* map) : Character(renderer, imagePath, startPosition, map)
{
	m_current_level_map = map;
	m_position = startPosition;
	m_current_frame = 0;
	m_frame_delay = ANIMATION_DELAY;
	m_collected = false;
	m_collision_radius = 15.0f;
	//m_injured = false;
	//m_alive = true;
	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();

}

CharacterCoin::~CharacterCoin()
{

}

void CharacterCoin::Render()
{


	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame,0,m_single_sprite_w,m_single_sprite_h };

	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y),m_single_sprite_w,m_single_sprite_h };

	
	
	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	
}
void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		m_frame_delay = ANIMATION_DELAY;

		m_current_frame++;

		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}
	}
	

}
