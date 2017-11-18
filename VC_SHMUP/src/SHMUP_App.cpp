#include "SHMUP_App.h"
#include "RenderManager.h"

SHMUP_App::SHMUP_App()
{
	m_pGameManager = NULL;
}

SHMUP_App::~SHMUP_App()
{
	if (m_pGameManager)
	{
		delete m_pGameManager;
	}
}

void SHMUP_App::Init()
{
	m_pGameManager = new SHMUP_GameManager(this);
}

void SHMUP_App::Shutdown()
{
	RenderManager::Get()->Cleanup();
}

void SHMUP_App::Update()
{
	VC_App::Update();

	if (m_pGameManager)
	{
		m_pGameManager->Update();
	}
}

void SHMUP_App::Render()
{
	RenderManager::Get()->Begin();
	RenderManager::Get()->Render();
	if (m_pGameManager)
	{
		m_pGameManager->Render();
	}
	RenderManager::Get()->End();
}