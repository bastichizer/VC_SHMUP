#include "SHMUP_PlayerSprite.h"
#include "InputManager.h"

SHMUP_PlayerSprite::SHMUP_PlayerSprite(int width, int height, int posX, int posY, WCHAR* texturePath, UIManager* uiManager) : Sprite(width, height, posX, posY, uiManager)
{
	Init(texturePath);
}

SHMUP_PlayerSprite::~SHMUP_PlayerSprite()
{

}

void SHMUP_PlayerSprite::Update()
{
	InputManager::Get()->GetMousePosition();
	if (InputManager::Get()->GetLeftMouseButton() == InputManager::LeftMouseButtonStatus::LB_Down)
	{
		int moveX = 0;
		int moveY = 0;
		InputManager::Get()->GetMouseMove(moveX, moveY);
		m_pos.x += (float)moveX * 0.000001f;
		m_pos.y += (float)moveY * 0.000001f;
	}
}

void SHMUP_PlayerSprite::Render(Camera* cam)
{
	Sprite::Render(cam);
}
