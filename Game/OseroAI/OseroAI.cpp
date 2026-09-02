#include "stdafx.h"
#include "OseroAI.h"
#include<vector>


OseroAI::OseroAI()
{
	std::random_device rd;
	m_rng.seed(rd());
}

OseroAI::~OseroAI()
{

}

bool OseroAI::Start()
{

return true;
}

void OseroAI::Update()
{

}

bool OseroAI::DecideMove(const Board& board, Board::Stone turn, int& outX, int& outY)
{
	/** 置ける場所を全て集める*/
	std::vector<std::pair<int, int>> candidates;

	for (int y = 0; y < Board::SIZE; ++y)
	{
		for (int x = 0; x < Board::SIZE; ++x)
		{
			if (board.CanPut(x, y, turn))
			{
				candidates.push_back({ x, y });
			}
		}
	}

	if (candidates.empty())
	{
		/** 置ける場所がない*/
		return false;
	}

	/** 駒を置ける場所からランダムに一つ選択*/
	/** */
	std::uniform_int_distribution<int> dist(0, static_cast<int>(candidates.size()) - 1);
	int index = dist(m_rng);

	/** ランダムに当たった番号の座標をoutX, outYに設定*/
	outX = candidates[index].first;
	outY = candidates[index].second;
	return true;
}
