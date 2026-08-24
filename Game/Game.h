#pragma once
#include "Level3DRender/LevelRender.h"
class Board;
class Piece_White;
class Piece_Black;
class Game : public IGameObject
{
public:
    Game();
    ~Game();
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	Board* m_board= nullptr;
	Piece_White* m_piece_White = nullptr;
	Piece_Black* m_piece_Black = nullptr;
};

