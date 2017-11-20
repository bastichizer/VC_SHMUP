#ifndef SHMUP_GAMEMANAGER_H
#define SHMUP_GAMEMANAGER_H

#include "RenderManager.h"
#include "UICamera.h"
#include "SHMUP_UIManager.h"
#include "GameManager.h"
#include "SHMUP_App.h"

class SHMUP_GameManager : public GameManager
{
public:
	SHMUP_GameManager(SHMUP_App* app);
	~SHMUP_GameManager();

	void Update();
	void Render();

	SHMUP_UIManager* GetUIManager() override { return m_pUIManager; }
	//UICamera* GetUICamera() { return m_pUICamera; }
	SHMUP_App* GetApp() override { return m_pApp; }

private:
	SHMUP_UIManager* m_pUIManager;
	//Camera m_testCamera;
	UICamera* m_pUICamera;

	SHMUP_App* m_pApp;
};

#endif
