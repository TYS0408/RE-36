#pragma once
class Piece_White: public IGameObject
{
public:
	Piece_White();
	~Piece_White();
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc,bool isWhiteTurn);

public:
	void SetPosition(const float x, const float y);
private:
	SpriteRender m_spriteRender;
	/**自分の番の時に光らせるボードUI*/
	SpriteRender m_whiteBoardSpriteRender;
	/**自分の番じゃないときに出すボードUI*/
	SpriteRender m_whiteGrayBoardSpriteRender;
};

