#include "SHMUP_GameManager.h"
#include "global.h"
#include "InputManager.h"
#include "SHMUP_App.h"

SHMUP_GameManager::SHMUP_GameManager(SHMUP_App* app)
{
	m_pApp = app;
	m_pUIManager = new SHMUP_UIManager(this);
	m_pUICamera = new UICamera;
}

SHMUP_GameManager::~SHMUP_GameManager()
{
	Sprite::Cleanup();
	delete m_pUIManager;
	delete m_pUICamera;
}

void SHMUP_GameManager::Update()
{
	m_pUICamera->UpdateViewMatrix();
	m_pUIManager->Update();
}

void SHMUP_GameManager::Render()
{
	m_pUIManager->Render(m_pUICamera);
}