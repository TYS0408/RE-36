#include "stdafx.h"
#include "GameOver.h"
namespace
{
	const char* FILEPATH = "Assets/Sprite/GameOver/GameOver.dds";

	const int WIDTH = 2000.0f;
	const int HIGHT = 500.0f;
}
GameOver::GameOver()
{

}


GameOver::~GameOver()
{
	
}


bool GameOver::Start()
{
	m_gameOverSpriteRender.Init(FILEPATH, WIDTH, HIGHT);
	return true;
}


void GameOver::Update()
{

}

void GameOver::Render(RenderContext& rc)
{
	m_gameOverSpriteRender.Draw(rc);
}


