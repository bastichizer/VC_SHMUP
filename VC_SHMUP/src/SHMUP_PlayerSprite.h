#pragma once

#include "Sprite.h"

class SHMUP_PlayerSprite : public Sprite
{
public:
	SHMUP_PlayerSprite(int width, int height, int posX, int posY, WCHAR* texturePath, UIManager* uiManager);
	~SHMUP_PlayerSprite();

	void Update();
	void Render(Camera* cam) override;

private:

};