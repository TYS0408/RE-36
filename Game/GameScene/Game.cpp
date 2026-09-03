#include "stdafx.h"
#include "Game.h"
#include"Board/Board.h"
#include "SoundManager/SoundManager.h"
Game::Game()
{

}

Game::~Game()
{

}


bool Game::Start()
{
	/** 乱数が毎回変わるようにする */
	srand((time(nullptr)));

	/** ゲーム開始時に、BGMをランダムに選びそれを再生 */
	
	int randomBGM = rand() % 3; // 0から2までのランダムな整数を生成

	SoundManager* soundManager = FindGO<SoundManager>("soundmanager");

	/** ループ再生、音量0.5でBGMを再生 */
	m_bgm = soundManager->PlayingSound(static_cast<enSound>(randomBGM), true, 0.5f); // ループ再生、音量0.5

	m_board = NewGO<Board>(0, "board_image");	return true;
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{

}