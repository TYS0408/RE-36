#include "stdafx.h"
#include "Game.h"
#include"Board.h"
#include"Piece_White.h"
#include"Piece_Black.h"
Game::Game()
{

}

Game::~Game()
{

}


bool Game::Start()
{
	m_board = NewGO<Board>(0, "board_image");
	return true;
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{

}