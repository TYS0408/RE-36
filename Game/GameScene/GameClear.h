#pragma once
class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

private:
	/** ゲームクリアの画像*/
	SpriteRender m_gameClearspriteRender;

};

