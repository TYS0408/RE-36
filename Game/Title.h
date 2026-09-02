#pragma once
class Title : public IGameObject
{
public:
	Title();
	~Title();

	bool Start();
	void Update();
	void Render(RenderContext& rc);

public:
	/** タイトル画面で行う処理 */
	void InTitle();

	/**　	タイトルの初期化が完了したかどうか*/
	bool IsReady()const
	{
		return m_isReady;
	}

private:
	/** フェード用の関数*/
	void FadeTitle();

private:
	/** タイトルスプライトレンダリング */
	SpriteRender m_spriteRender;

	/** タイトル画面でスタートを促すスプライト*/
	SpriteRender m_titlePressStartSpriteRender;

	enum enTitleState 
	{
		/** フェードイン*/
		FadeIn,
		/** フェードアウト*/
		FadeOut,
	};
	enTitleState m_titleState = FadeIn;

	/** α値の変数*/
	float m_titleAlpha = 0.0f;

	/** 点滅用タイマー */
	float m_blinkTimer = 0.0f;
	/** 点滅間隔*/
	float m_titleBlinkInterval = 0.2f;

	/** 点滅が終わる時間*/
	float m_titleFinalBlinkTime = 1.0f;

	/** スタートボタンが押されたかどうか*/
	bool m_isStartButtonPressed = false;

	/** タイトルの初期化が完了したかどうかのフラグ */
	bool m_isReady = false;

	/** 点滅の表示/非表示切り替えフラグ */
	bool m_blinkVisible = true;

};

