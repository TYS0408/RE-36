#pragma once
#include"Piece_White.h"
#include"Piece_Black.h"
class Board :public IGameObject
{
public:
	//NOTE:このstatic constexprはコンパイル時に確定する定数かつ、
	//オセロボードの大きさだからクラスに一つだけあればでよいのでstaticを使う。
	static constexpr int SIZE = 6;
	Board();
	~Board();
	enum Stone
	{
		EMPTY,
		BLACK,
		WHITE
	};
	bool Start();
	void Update();
	void Render(RenderContext& rc)override;
public:
	void First();
	//このマスに駒を置けるか
	bool CanPut(int x, int y, Stone turn)const;
	//盤面に駒を置く
	//これは状態を変更する関数だからconstはなし
	void PutStone(int x, int y, Stone turn);
	//駒を置ける場所はあるか
	bool HasValidMove(Stone turn)const;
	void CountStone(int& black, int& white)const;

	Stone GetStone(int x, int y)const;

private:
	Stone m_board[SIZE][SIZE];
	Piece_White m_piece_White[SIZE][SIZE];
	Piece_Black m_piece_Black[SIZE][SIZE];
	SpriteRender m_spriteRender;
private:
	//挟んだ駒をひっくり返す
	void Reverse(int x, int y, Stone turn);
	/** 置ける場所が盤面の範囲内に収まっているか*/
	bool IsInside(int x, int y)const;
};

