#pragma once
#include"Board/Board.h"
#include<random>
class OseroAI 
{
public:
	OseroAI();
	~OseroAI();

	bool Start();
	void Update();

	bool DecideMove(const Board& board, Board::Stone turn, int& outX, int& outY);


private:

	/** 2の19937乗-１の分までの数字を扱うことが出来るので
	質のいい乱数を作ることが出来る*/
	std::mt19937 m_rng;
};

