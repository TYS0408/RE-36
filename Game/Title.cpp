#include "stdafx.h"
#include "Title.h"
#include"GameScene/Game.h"
namespace
{
	const char* FILEPATH = "Assets/Sprite/Title/Title.dds";
	const int WIDTH = 1920.0f;
	const int HIGHT = 1080.0f;
}

Title::Title()
{

}

Title::~Title()
{

}


bool Title::Start()
{
	m_spriteRender.Init(FILEPATH, WIDTH, HIGHT);
	return true;
}

void Title::Update()
{
	/** 何かボタンを押されたらゲームシーンへ移行*/
	if(g_pad[0]->IsPressAnyKey() &&!m_isStartButtonPressed)
	{
		m_isStartButtonPressed = true;
		
		NewGO<Game>(0, "game");
		DeleteGO(this);
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
}