#ifndef SHMUP_GAMEMANAGER_H
#define SHMUP_GAMEMANAGER_H

#include "RenderManager.h"
#include "UICamera.h"
#include "SHMUP_UIManager.h"

class SHMUP_App;

class SHMUP_GameManager
{
public:
	SHMUP_GameManager(SHMUP_App* app);
	~SHMUP_GameManager();

	void Update();
	void Render();

	SHMUP_UIManager* GetUIManager() { return m_pUIManager; }
	UICamera* GetUICamera() { return m_pUICamera; }
	SHMUP_App* GetApp() { return m_pApp; }

private:
	SHMUP_UIManager* m_pUIManager;
	//Camera m_testCamera;
	UICamera* m_pUICamera;

	SHMUP_App* m_pApp;
};

#endif
