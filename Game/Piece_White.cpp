#include "stdafx.h"
#include "Piece_White.h"

namespace
{
	const char* FILEPATH = "Assets/Osero/White.dds";
	const int WIDTH = 200.0f;
	const int HIGHT = 150.0f;
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
	return true;
}


void Piece_White::Update()
{

}


void Piece_White::SetPosition(float x, float y)
{
	m_spriteRender.SetPosition({ x,y,0.0f });
}

void Piece_White::Render(RenderContext& rc)
{
	m_spriteRender.Update();
	m_spriteRender.Draw(rc);
}

