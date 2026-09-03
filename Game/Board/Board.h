#pragma once
#include"Piece/Piece_White.h"
#include"Piece/Piece_Black.h"
#include"ScalePopupAnimation/ScalePopupAnimation.h"
class GameOver;
class GameClear;
class OseroAI;
class SoundManager;
class Board :public IGameObject
{
public:
	//NOTE:このstatic constexprはコンパイル時に確定する定数かつ、
	//オセロボードの大きさだからクラスに一つだけあればでよいのでstaticを使う。
	static constexpr int SIZE = 6;
	Board();
	~Board();
	enum Stone
	{
		EMPTY,
		BLACK,
		WHITE
	};
	bool Start();
	void Update()override;
	void Render(RenderContext& rc)override;
public:
	void First();
	//このマスに駒を置けるか
	bool CanPut(int x, int y, Stone turn)const;

	//bool WorldPosToBoardIndex(float worldx, float worldy, int& outX, int& outY)const;
	//盤面に駒を置く
	//これは状態を変更する関数だからconstはなし
	void PutStone(int x, int y, Stone turn);
	//駒を置ける場所はあるか
	bool HasValidMove(Stone turn)const;
	void CountStone(int& black, int& white)const;

	Stone GetStone(int x, int y)const;

private:
	/** 石が置ける範囲*/
	Stone m_board[SIZE][SIZE];
	/** 最初は黒の番からスタートする*/
	Stone m_turn;
	
	bool m_leftButtonWasPressed = false;
	/** ターンのスライドアニメ―ション中かどうか*/
	bool m_isPlayTurnAnimation = false;

	bool WorldPosToBoardIndex(float worldX, float worldY, int& outX, int& outY) const;

	Piece_White m_piece_White[SIZE][SIZE];
	Piece_Black m_piece_Black[SIZE][SIZE];
	SpriteRender m_spriteRender;

	/** 駒を置ける場所を示すヒント用スプライト*/
	SpriteRender m_hintSprite[SIZE][SIZE];

	/** 手番を表示するためのUI*/
	/** 黒*/
	SpriteRender m_blackTurnSprite;
	/** 白*/
	SpriteRender m_WhiteTurnSprite;

	/** 「FINISH！」の画像スプライト*/
	SpriteRender m_finishSprite;

	/** スケールポップアップアニメーション*/
	ScalePopupAnimation  m_scalePopupAnimation;

	

	/**ゲームクリア*/
	GameOver* m_GameOver= nullptr;
	/** ゲームオーバー*/
	GameClear* m_GameClear = nullptr;

	/** オセロの白い駒をランダムに置くようにする */
	OseroAI* m_ai = nullptr;

	enum class GameState
	{
		Playing,
		Finishing,
		GameOver,
		GameClear,
	};
	GameState m_gameState = GameState::Playing;

	/** 手番アニメーション用enum*/
	enum class TurnUIState
	{
		SlideIn,/** 右から中央へ移動中*/
		Hold,/** 中央で停止中*/
		SlideOut,/** 中央から画面外へ移動中*/
		Idle/** 画面外で待機中*/
	};

	TurnUIState m_turnUIState = TurnUIState::SlideIn;
	/** 経過時間*/
	float m_turnUITimer = 0.0f;
	/** 手番UIの現在のX座標*/
	float m_turnUIPosX = 0.0f;
	/** 前フレームの手番*/
	Stone m_lastTurn = EMPTY;

	/** 石を置く音*/
	SoundSource* m_putStoneSound;

	/** サウンドマネージャー */
	SoundManager* m_soundManager = nullptr;

private:
	//挟んだ駒をひっくり返す
	void Reverse(int x, int y, Stone turn);
	/** 置ける場所が盤面の範囲内に収まっているか*/
	bool IsInside(int x, int y)const;

	/**マウス入力を見て、クリックされていたら石を置く処理*/
	void HandleMouseInput();

	/** 手番アニメーション更新処理*/
	void UpdateTurnUI();
	/** ゲームを終える処理*/
	void CheckGameEnd();
	/** AIの更新処理*/
	void UpdateAI();
	/** スライドアニメーション開始処理*/
	void StartTurnAnimation();

	/** 演出後の勝敗判定*/
	void FinalizeGameEnd();

};


