#include "stdafx.h"
#include "Board.h"


namespace
{
	//オセロの盤面
	const char* FILEPATHBOARD = "Assets/Osero/Board.dds";
	const int WIDTHBOARD = 1000.0f;
	const int HIGHTBOARD = 1000.0f;

	/** 8方向(左上から時計回り)*/
	const int DX[8] = { -1,0,1,-1,1,-1,0,1 };
	const int DY[8] = { -1,-1,-1,0,0,1,1,1 };
}
Board::Board()
{

}

Board::~Board()
{

}

bool Board::IsInside(int x, int y)const
{
	
	return x >= 0 && x < SIZE && y >= 0 &&y <  SIZE;
}

bool Board::CanPut(int x, int y, Stone turn)const
{
	/** 盤面外の場合は駒を置けない*/
	if (!IsInside(x, y)) return false;
	/** 既に駒が置いてある場合も置けない*/
	if (m_board[y][x] != EMPTY)return false;
	/**今の手番が黒なら白に白なら黒に変える */
	/** 条件 ? 条件がtrueのときの値 : 条件がfalseのときの値*/
	Stone opponent = (turn == BLACK) ? WHITE : BLACK;

	/** 8方向全てチェックする*/
	for (int dir = 0; dir < 8; dir++)
	{
		int nx = x + DX[dir];
		int ny = y + DY[dir];
		/**相手の石があるかどうか */
		bool hasOpponentBetween = false;

		/** 相手の石が連続している間、進み続ける*/
		while (IsInside(nx,ny) &&m_board[ny][nx] ==opponent)
		{
			nx += DX[dir];
			ny += DY[dir];
			hasOpponentBetween = true;
		}

		/** 相手の石を一つ以上挟んだ先に自分の石があれば置ける*/
		if (hasOpponentBetween && IsInside(nx, ny) && m_board[ny][nx] == turn)
		{
			return true;
		}
	}
	return false;
}


bool Board::Start()
{
	m_spriteRender.Init(FILEPATHBOARD, WIDTHBOARD, HIGHTBOARD);
	m_spriteRender.SetPosition({ 0.0f,0.0f,0.0f });
	First();

	/** 全マス分のインスタンスを初期化*/
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			m_piece_White[y][x].Start();
			m_piece_Black[y][x].Start();
		}
	}
	return true;
}

void Board::Update()
{

}
//初期化
void Board::First()
{

	//盤面を全てEMPTY（何も置かれていない状態)にしている
	for (int y = 0; y < SIZE; y++)
		for (int x = 0; x < SIZE; x++)
			m_board[y][x] = EMPTY;

	//6×6の盤面の中央は(2,2)(3,3)だから
	// 盤面から0,1,2,……と数える
	      //行//列
	m_board[2][2] = WHITE;
	m_board[3][3] = WHITE;
	m_board[2][3] = BLACK;
	m_board[3][2] = BLACK;

}

Board::Stone Board::GetStone(int x, int y)const
{
	return m_board[y][x];
}


void Board::Render(RenderContext& rc)
{
	//盤面の表示
	m_spriteRender.Draw(rc);
	m_spriteRender.Update();
	/** 盤面の中心が(0,0)なので
	石の盤面を左上端(WIDTHBORAD/2,-HIGHTBOARD/2)を基準にする*/
	const float startX = -WIDTHBOARD * 0.5f;
	const float startY = -HIGHTBOARD * 0.5f;
	const float cellSize = WIDTHBOARD / (float)SIZE;
	

	//ここで盤面のデータをみて初期位置の石を配置
	for (int y = 0; y < SIZE; y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			//石の描画位置の計算
			float drawX = startX + x * cellSize + cellSize * 0.5f;
			/**ワールド座標(Y+が上)に変換するため上下を反転させる */
			float drawY = startY + (SIZE - 1 - y) * cellSize + cellSize * 0.5f;

			if (m_board[y][x] == BLACK)
			{
				m_piece_Black[y][x].SetPosition(drawX, drawY);
				m_piece_Black[y][x].Render(rc);
			}
			else if (m_board[y][x] == WHITE)
			{
				m_piece_White[y][x].SetPosition(drawX, drawY);
				m_piece_White[y][x].Render(rc);
			}
		}
	}
}