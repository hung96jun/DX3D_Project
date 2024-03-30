#include "GameManager.h"

GameManager* GameManager::Instance = nullptr;

GameManager::GameManager()
{
	Create();
}

GameManager::~GameManager()
{
}

GameManager* GameManager::Get()
{
	if (Instance == nullptr)
		Instance = new GameManager();

	return Instance;
}

void GameManager::Destroy()
{
	delete Instance;
}

void GameManager::Create()
{
}

void GameManager::Update()
{
}

void GameManager::Render()
{
}
