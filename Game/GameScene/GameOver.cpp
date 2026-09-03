#include "stdafx.h"
#include "GameOver.h"
namespace
{
	const char* FILEPATH = "Assets/Sprite/GameOver/GameOver.dds";
	const int WIDTH = 2000.0f;
	const int HIGHT = 700.0f;


	/** 黒い駒アイコンの画像パス*/
	const char* FILEPATH_BLACK_PIECE = "Assets/Sprite/Osero/Black.dds";

	/** 白い駒アイコンの画像パス*/
	const char* FILEPATH_WHITE_PIECE = "Assets/Sprite/Osero/White.dds";


	/** 下段の駒数表示位置*/
	const float NUMBER_WIDTH = 150.0f;
	const float NUMBER_HEIGHT = 100.0f;
	const float NUMBER_SPACING = 50.0f;

	/** 駒アイコンのサイズ*/
	const float PIECE_ICON_WIDTH = 200.0f;
	const float PIECE_ICON_HEIGHT = 100.0f;


	/** 黒い駒アイコンの表示位置*/
	const float BLACK_PIECE_X = -100.0f;
	const float BLACK_PIECE_Y = -50.0f;


	/** 黒い駒の数の表示位置*/
	const float BLACK_NUMBER_X = -100.0f;
	const float BLACK_NUMBER_Y = -200.0f;

	/** 白い駒アイコンの表示位置*/
	const float WHITE_ICON_X = 100.0f;
	const float WHITE_ICON_Y = -50.0f;

	/** 白い駒の数の表示位置*/
	const float WHITE_NUMBER_X = 100.0f;
	const float WHITE_NUMBER_Y = -200.0f;
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

	m_blackPieceCountRender.Init(NumberColor::Black, NUMBER_WIDTH, NUMBER_HEIGHT);
	m_whitePieceCountRender.Init(NumberColor::White, NUMBER_WIDTH, NUMBER_HEIGHT);

	/** 黒い駒アイコンの初期化*/
	m_blackPieceIcon.Init(FILEPATH_BLACK_PIECE, PIECE_ICON_WIDTH, PIECE_ICON_HEIGHT);
	/** 白い駒アイコンの初期化*/	
	m_whitePieceIcon.Init(FILEPATH_WHITE_PIECE, PIECE_ICON_WIDTH, PIECE_ICON_HEIGHT);
	return true;
}

void GameOver::SetPieceCount(int blackCount, int whiteCount)
{
	m_blackCount = blackCount;
	m_whiteCount = whiteCount;
}


void GameOver::Update()
{

}

void GameOver::Render(RenderContext& rc)
{
	/** ゲームオーバー画面の描画*/
	m_gameOverSpriteRender.Draw(rc);

	/** 駒数の描画*/
	m_blackPieceCountRender.Draw(rc, m_blackCount, BLACK_NUMBER_X, BLACK_NUMBER_Y, NUMBER_SPACING);
	m_whitePieceCountRender.Draw(rc, m_whiteCount, WHITE_NUMBER_X, WHITE_NUMBER_Y, NUMBER_SPACING);

	/** 白駒アイコンの描画*/
	m_whitePieceIcon.SetPosition({ WHITE_ICON_X, WHITE_ICON_Y,0.0f });
	m_whitePieceIcon.Update();
	m_whitePieceIcon.Draw(rc);

	/** 黒駒アイコンの描画*/
	m_blackPieceIcon.SetPosition({ BLACK_PIECE_X, BLACK_PIECE_Y,0.0f });
	m_blackPieceIcon.Update();
	m_blackPieceIcon.Draw(rc);

}


