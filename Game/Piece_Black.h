#pragma once
class Piece_Black: public IGameObject
{
public:
	Piece_Black();
	~Piece_Black();
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	void SetPosition(const float x, const float y);
private:
	SpriteRender m_spriteRender;
};

