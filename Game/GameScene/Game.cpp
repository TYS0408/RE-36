#include "stdafx.h"
#include "Game.h"
#include"Board/Board.h"
Game::Game()
{

}

Game::~Game()
{

}


bool Game::Start()
{
	m_board = NewGO<Board>(0, "board_image");	return true;
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{

}