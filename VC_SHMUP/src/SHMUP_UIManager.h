#ifndef SHMUP_UIMANAGER_H
#define SHMUP_UIMANAGER_H

#include "UIManager.h"

class SHMUP_GameManager;

class SHMUP_UIManager : public UIManager
{
public:
	SHMUP_UIManager(SHMUP_GameManager* gameManager);
	~SHMUP_UIManager();

	void Update() override;
	
	void ZoomInPressed(int n);
	void ZoomOutPressed(int n);
	void GridTogglePressed(int n);
	void ShopButtonPressed(int n);

	SHMUP_GameManager* GetGameManager() { return m_pGameManager; }

private:
	SHMUP_GameManager* m_pGameManager;
};

#endif // SHMUP_UIMANAGER_H
