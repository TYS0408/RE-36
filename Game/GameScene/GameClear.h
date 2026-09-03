#pragma once
#include"NumberRender/NumberRender.h"
class GameClear : public IGameObject
{
public:
	GameClear();
	~GameClear();
public:
	bool Start();
	void Update();
	void Render(RenderContext& rc);

	/** 黒駒と白駒の数を設定する*/
	void SetPieceCount(int blackCount, int whiteCount);

private:
	/** ゲームクリアの画像*/
	SpriteRender m_gameClearspriteRender;


	/** 黒い駒の数の数字*/
	NumberRender m_blackPieceCountRender;
	/** 白い駒の数の数字*/
	NumberRender m_whitePieceCountRender;

	/** 黒駒アイコン*/
	SpriteRender m_blackPieceIcon;
	/** 白駒アイコン*/
	SpriteRender m_whitePieceIcon;
	/** 黒い駒の数*/
	uint8_t m_blackCount = 0;
	/** 白い駒の数*/
	uint8_t m_whiteCount = 0;
};

