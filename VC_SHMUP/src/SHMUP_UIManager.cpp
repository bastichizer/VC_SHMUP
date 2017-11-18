#include "SHMUP_UIManager.h"
#include "global.h"
#include "OverlayGrid.h"
#include "SHMUP_GameManager.h"

SHMUP_UIManager::SHMUP_UIManager(SHMUP_GameManager* gameManager) : UIManager()
{
	m_pGameManager = gameManager;

	// populate the sprite vectors, making sure to fill in render depth order from back to front to avoid alpha blending issues

	// initialize background map elements from XML file
	tinyxml2::XMLDocument xmlDoc;
	xmlDoc.LoadFile("data\\map.xml");
	int mapWidth = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("GameMap")->FirstChildElement("width")->GetText());
	int mapHeight = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("GameMap")->FirstChildElement("height")->GetText());
	int mapPosX = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("GameMap")->FirstChildElement("posX")->GetText());
	int mapPosY = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("GameMap")->FirstChildElement("posY")->GetText());
	const char* mapPath(xmlDoc.FirstChildElement("map")->FirstChildElement("GameMap")->FirstChildElement("path")->GetText());
	size_t strSize = strlen(mapPath) + 1;
	WCHAR* mapPathW = new WCHAR[strSize];
	size_t* pConv = NULL;
	mbstowcs_s(pConv, mapPathW, strSize, mapPath, strSize - 1);
	m_backgroundVector.push_back(new BackgroundSprite(mapWidth, mapHeight, mapPosX, mapPosY, mapPathW));
	delete[] mapPathW;

	int gridWidth = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("OverlayGrid")->FirstChildElement("width")->GetText());
	int gridHeight = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("OverlayGrid")->FirstChildElement("height")->GetText());
	int gridOffsetX = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("OverlayGrid")->FirstChildElement("offsetX")->GetText());
	int gridOffsetY = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("OverlayGrid")->FirstChildElement("offsetY")->GetText());
	int gridSideLength = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("OverlayGrid")->FirstChildElement("gridSideLength")->GetText());
	int gridCenterX = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("OverlayGrid")->FirstChildElement("gridCenterX")->GetText());
	int gridCenterY = atoi(xmlDoc.FirstChildElement("map")->FirstChildElement("OverlayGrid")->FirstChildElement("gridCenterY")->GetText());
	const char* overlayPath(xmlDoc.FirstChildElement("map")->FirstChildElement("OverlayGrid")->FirstChildElement("path")->GetText());
	strSize = strlen(overlayPath) + 1;
	WCHAR* overlayPathW = new WCHAR[strSize];
	pConv = NULL;
	mbstowcs_s(pConv, overlayPathW, strSize, overlayPath, strSize - 1);
	m_backgroundVector.push_back(new OverlayGrid(gridWidth, gridHeight, 0, 0, gridOffsetX, gridOffsetY, gridSideLength, gridCenterX, gridCenterY, overlayPathW));
	delete[] overlayPathW;

	// initialize mid ground elements from data saved in map XML file

	// initialize foreground UI
	// Bottom bar UI background
	m_foregroundVector.push_back(new Sprite(g_windowWidth, g_windowHeight / 4, 0, 0));
	m_foregroundVector[0]->Init(L"img\\MenuBackground.dds");

	// Map zoom buttons and bind event delegates
	m_foregroundVector.push_back(new UIButton(64, 64, g_windowWidth - 64, g_windowHeight - g_windowHeight / 3, 0.8f, 1.0f, 0.5f, L"img\\zoomin.dds"));
	UIButton* pButton = static_cast<UIButton*>(m_foregroundVector.back());
	pButton->RegisterButtonWithInputManager();
	m_buttonDelegates.push_back(new Delegate<void, int>(this, &SHMUP_UIManager::ZoomInPressed));
	pButton->PushDelegate(m_buttonDelegates.back());

	m_foregroundVector.push_back(new UIButton(64, 64, g_windowWidth - 64, g_windowHeight - g_windowHeight / 3 - 128, 0.8f, 1.0f, 0.5f, L"img\\zoomout.dds"));
	pButton = static_cast<UIButton*>(m_foregroundVector.back());
	pButton->RegisterButtonWithInputManager();
	m_buttonDelegates.push_back(new Delegate<void, int>(this, &SHMUP_UIManager::ZoomOutPressed));
	pButton->PushDelegate(m_buttonDelegates.back());

	// Add button for toggling the grid overlay on and off
	m_foregroundVector.push_back(new UIButton(64, 32, g_windowWidth - 70, 25, 1.0f, 1.0f, 0.5f, L"img\\ToggleGridButton.dds"));
	pButton = static_cast<UIButton*>(m_foregroundVector.back());
	pButton->RegisterButtonWithInputManager();
	m_buttonDelegates.push_back(new Delegate<void, int>(this, &SHMUP_UIManager::GridTogglePressed));
	pButton->PushDelegate(m_buttonDelegates.back());

	// Add shop menu button
	m_foregroundVector.push_back(new UIButton(64, 64, g_windowWidth - 70, 85, 1.0f, 1.0f, 0.5f, L"img\\shop.dds"));
	pButton = static_cast<UIButton*>(m_foregroundVector.back());
	pButton->RegisterButtonWithInputManager();
	m_buttonDelegates.push_back(new Delegate<void, int>(this, &SHMUP_UIManager::ShopButtonPressed));
	pButton->PushDelegate(m_buttonDelegates.back());
}

SHMUP_UIManager::~SHMUP_UIManager()
{

}

void SHMUP_UIManager::Update()
{

}

void SHMUP_UIManager::ZoomInPressed(int n)
{
	if (m_currentViewScale < 2.0f)
	{
		m_currentViewScale += 0.5f;
	}
	static_cast<GameMap*>(m_backgroundVector[0])->ZoomIn();
	static_cast<OverlayGrid*>(m_backgroundVector[1])->ZoomIn();

	for (int i = 0; i < (int)m_midgroundVector.size(); ++i)
	{
		m_midgroundVector[i]->SetScale(m_currentViewScale);
	}
}

void SHMUP_UIManager::ZoomOutPressed(int n)
{
	if (m_currentViewScale > 1.0f)
	{
		m_currentViewScale -= 0.5f;
	}
	static_cast<GameMap*>(m_backgroundVector[0])->ZoomOut();
	static_cast<OverlayGrid*>(m_backgroundVector[1])->ZoomOut();

	for (int i = 0; i < (int)m_midgroundVector.size(); ++i)
	{
		m_midgroundVector[i]->SetScale(m_currentViewScale);
	}
}

void SHMUP_UIManager::GridTogglePressed(int n)
{
	static_cast<OverlayGrid*>(m_backgroundVector[1])->ToggleOverlayGridActive();
}

void SHMUP_UIManager::ShopButtonPressed(int n)
{

}
