#pragma once
class Piece_White: public IGameObject
{
public:
	Piece_White();
	~Piece_White();
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

public:
	void SetPosition(const float x, const float y);
private:
	SpriteRender m_spriteRender;
};

