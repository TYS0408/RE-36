#include "stdafx.h"
#include "Piece_Black.h"
namespace
{
	const char* FILEPATH = "Assets/Sprite/Osero/Black.dds";
	const int WIDTH = 200.0f;
	const int HIGHT = 150.0f;

	/** 自分の番の時に光らせるUIのファイルパス*/
	const char* BLACKBOARDFILEPATH = "Assets/Sprite/OseroBoard/Black_Board.dds";
	const int BLACKBOARDWIDTH = 1000.0f;
	const int BLACKBOARDHIGHT = 500.0f;

	/** 自分の番じゃないときに出す薄暗いボードUI*/
	const char* BLACKGRAYBOARDFILEPATH = "Assets/Sprite/OseroBoard/BlackBoard_Dark.dds";





}

Piece_Black::Piece_Black()
{

}

Piece_Black::~Piece_Black()
{

}


bool Piece_Black::Start()
{
	m_spriteRender.Init(FILEPATH, WIDTH, HIGHT);

	/** 自分の番の時に出すボードUI*/
	m_blackBoradSpriteRender.Init(BLACKBOARDFILEPATH, BLACKBOARDWIDTH, BLACKBOARDHIGHT);
	m_blackBoradSpriteRender.SetPosition({ -700.0f,100.0f,0.0f });
	m_blackBoradSpriteRender.Update();

	/** 自分の番じゃないときに出す薄暗いボードUI*/
	m_blackGrayBoardSpriteRender.Init(BLACKGRAYBOARDFILEPATH, BLACKBOARDWIDTH, BLACKBOARDHIGHT);
	m_blackGrayBoardSpriteRender.SetPosition({ -700.0f,100.0f,0.0f, });
	m_blackGrayBoardSpriteRender.Update();
	return true;
}


void Piece_Black::Update()
{

}


void Piece_Black::SetPosition(float x, float y)
{
	m_spriteRender.SetPosition({ x,y,0.0f });
}

void Piece_Black::Render(RenderContext& rc, bool isBlackTurn)
{
	m_spriteRender.Update();
	m_spriteRender.Draw(rc);
	if (isBlackTurn)
	{
		/** 自分の番なら明るいボードを表示*/
		m_blackBoradSpriteRender.Draw(rc);
	}
	else
	{
		/** 自分の番じゃないなら薄暗いボードを表示*/
		m_blackGrayBoardSpriteRender.Draw(rc);
	}
	

	
}

