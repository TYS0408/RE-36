#include "stdafx.h"
#include "Piece_Black.h"
namespace
{
	const char* FILEPATH = "Assets/Osero/Black.dds";
	const int WIDTH = 200.0f;
	const int HIGHT = 150.0f;
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
	return true;
}


void Piece_Black::Update()
{

}


void Piece_Black::SetPosition(float x, float y)
{
	m_spriteRender.SetPosition({ x,y,0.0f });
}

void Piece_Black::Render(RenderContext& rc)
{
	m_spriteRender.Update();
	m_spriteRender.Draw(rc);
}

