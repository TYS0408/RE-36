#include "stdafx.h"
#include "Piece_White.h"

namespace
{
	const char* FILEPATH = "Assets/Sprite/Osero/White.dds";
	const int WIDTH = 200.0f;
	const int HIGHT = 150.0f;
	/**今盤面に自分の駒が何枚あるかを示すUIのファイルパス*/
	const char* WHITEBOARDFILEPATH = "Assets/Sprite/OseroBoard/White_Board.dds";
	const int WHITEBOARDWIDTH = 1000.0f;
	const int WHITEBOARDHIGHT = 500.0f;

	/** 灰色のボード*/
	const char* GRAYWHITEBOARDFILEPATH = "Assets/Sprite/OseroBoard/WhiteBoard_Dark.dds";

}
Piece_White::Piece_White()
{

}


Piece_White::~Piece_White()
{

}


bool Piece_White::Start()
{
	m_spriteRender.Init(FILEPATH, WIDTH, HIGHT);
	/** 白が番の時に光らせる*/
	m_whiteBoardSpriteRender.Init(WHITEBOARDFILEPATH, WHITEBOARDWIDTH,WHITEBOARDHIGHT);
	m_whiteBoardSpriteRender.SetPosition({ 700.0f,100.0f,0.0f });
	m_whiteBoardSpriteRender.Update();

	/** 白が番じゃない時に出す*/
	m_whiteGrayBoardSpriteRender.Init(GRAYWHITEBOARDFILEPATH, WHITEBOARDWIDTH, WHITEBOARDHIGHT);
	m_whiteGrayBoardSpriteRender.SetPosition({ 700.0f,100.0f,0.0f });
	m_whiteGrayBoardSpriteRender.Update();


	return true;
}


void Piece_White::Update()
{

}


void Piece_White::SetPosition(float x, float y)
{
	m_spriteRender.SetPosition({ x,y,0.0f });
}

void Piece_White::Render(RenderContext& rc,bool isWhiteTurn)
{
	m_spriteRender.Update();
	m_spriteRender.Draw(rc);

	if (isWhiteTurn)
	{
		/** 自分の番なら明るいボードを描画*/
		m_whiteBoardSpriteRender.Draw(rc);
	}
	else
	{
		/** 自分の番なら薄暗いボードを描画*/
		m_whiteGrayBoardSpriteRender.Draw(rc);
	}
}

