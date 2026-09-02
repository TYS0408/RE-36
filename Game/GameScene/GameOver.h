#pragma once
class GameOver : public IGameObject
{
public:
	GameOver();
	~GameOver();

public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	SpriteRender m_gameOverSpriteRender;

};

