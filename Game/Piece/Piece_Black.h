#pragma once
class Piece_Black: public IGameObject
{
public:
	Piece_Black();
	~Piece_Black();
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc,bool isBlackTurn);

	void SetPosition(const float x, const float y);
private:
	/** 駒のスプライト*/
	SpriteRender m_spriteRender;
	/** 自分の番の時に光らせるボードスプライト*/
	SpriteRender m_blackBoradSpriteRender;

	/**自分の番じゃないときに出す薄暗いボードUI*/
	SpriteRender m_blackGrayBoardSpriteRender;


};

