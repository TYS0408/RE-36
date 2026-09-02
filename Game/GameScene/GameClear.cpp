#include "stdafx.h"
#include "GameClear.h"
namespace
{
	const char* FILEPATH = "Assets/Sprite/GameClear/GameClear.dds";
	const int  WIDTH = 2000.0f;
	const int HIGHT = 500.0f;
}
GameClear::GameClear()
{

}

GameClear::~GameClear()
{

}


bool GameClear:: Start()
{
	m_gameClearspriteRender.Init(FILEPATH, WIDTH, HIGHT);
	return true;
}


void GameClear::Update()
{

}


void GameClear::Render(RenderContext& rc)
{
	m_gameClearspriteRender.Draw(rc);
}