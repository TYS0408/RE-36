#include "stdafx.h"
#include "Title.h"
#include"GameScene/Game.h"
namespace
{
	/** タイトルスプライトのファイルパス */
	const char* FILEPATH = "Assets/Sprite/Title/Title.dds";
	/** タイトルスプライトの幅 */
	const int WIDTH = 1920.0f;
	/** タイトルスプライトの高さ */
	const int HIGHT = 1080.0f;

	/** タイトルを促す画像のファイルパス*/
	const char* FILEPATH_PRESSSTART = "Assets/Sprite/Title/PressAnyButton.dds";

	/** タイトルを促す画像の座標*/
	const Vector3 TITLE_PRESSSTART_POS = { 0.0f,-350.0f,0.0f, };

	/** タイトルを促す画像の大きさ*/
	constexpr int TITLE_PRESSSTART_WIDTH = 1400.0f;
	constexpr int TITLE_PRESSSTART_HIGHT = 1700.0f;

	/** タイトル画面での点滅の最後の間隔*/
	constexpr float TITLE_FINAL_BLINK_INTERVAL = 1.0f;
}

Title::Title()
{

}

Title::~Title()
{

}


bool Title::Start()
{
	m_spriteRender.Init(FILEPATH, WIDTH, HIGHT);

	m_titlePressStartSpriteRender.Init(FILEPATH_PRESSSTART, TITLE_PRESSSTART_WIDTH, TITLE_PRESSSTART_HIGHT);
	m_titlePressStartSpriteRender.SetPosition(TITLE_PRESSSTART_POS);
	m_titlePressStartSpriteRender.Update();

	/** ここまで来たら初期化完了にする */
	m_isReady = true;
	return true;
}

void Title::Update()
{
	/** タイトルでの処理*/
	InTitle();
	/** フェード処理*/
	FadeTitle();
}

void Title::InTitle()
{
	/** 何かボタンを押されたらゲームシーンへ移行*/
	if (g_pad[0]->IsPressAnyKey() && !m_isStartButtonPressed)
	{
		m_isStartButtonPressed = true;
	}

	if (m_isStartButtonPressed)
	{
		m_titleFinalBlinkTime -= g_gameTime->GetFrameDeltaTime();

		/** 点滅間隔をだんだん短くしていく（速く点滅するようになる） */
		m_titleBlinkInterval -= g_gameTime->GetFrameDeltaTime() * m_titleBlinkInterval * 0.5f;
		if (m_titleBlinkInterval < 0.03f)
		{
			m_titleBlinkInterval = 0.03f; // 速くなりすぎ防止の下限
		}

		/** 点滅タイマーを進める */
		m_blinkTimer += g_gameTime->GetFrameDeltaTime();
		if (m_blinkTimer >= m_titleBlinkInterval)
		{
			m_blinkTimer = 0.0f;
			m_blinkVisible = !m_blinkVisible; // 表示/非表示を切り替える
		}

		if (m_titleFinalBlinkTime <= 0.0f)
		{
			m_isStartButtonPressed = false;
			/** 点滅が終わったらゲームを開始*/
			NewGO<Game>(0, "game");
			DeleteGO(this);
		}
	}
}


void Title::FadeTitle()
{
	if (!m_isStartButtonPressed)
	{
		/** フェード処理*/
		switch (m_titleState)
		{
		case Title::FadeIn:
			m_titleAlpha += g_gameTime->GetFrameDeltaTime();
			if (m_titleAlpha >= 1.0f)
			{
				m_titleAlpha = 1.0f;
				m_titleState = FadeOut;
			}
			break;
		case Title::FadeOut:
			m_titleAlpha -= g_gameTime->GetFrameDeltaTime();
			if (m_titleAlpha <= 0.0f)
			{
				m_titleAlpha = 0.0f;
				m_titleState = FadeIn;
			}
			break;
		}
	}
}

void Title::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	/** ボタンが押されていない場合にPress Start画像を描画 */
	if (!m_isStartButtonPressed)
	{
		/** α値が0.0fより大きい時に描画する*/
		if (m_titleAlpha > 0.0f)
		{
			m_titlePressStartSpriteRender.SetMulColor(
				Vector4(1.0f, 1.0f, 1.0f, m_titleAlpha));

			m_titlePressStartSpriteRender.Draw(rc);
		}
		return;
	}

	/** 点滅処理 */
/* 点滅の間隔が偶数のときは描画する */
	if (static_cast<int>(m_titleBlinkInterval * 2) % 2 == 0)
	{
		m_titlePressStartSpriteRender.SetMulColor(
			Vector4(
				1.0f,
				1.0f,
				1.0f,
				1.0f));
		m_titlePressStartSpriteRender.Draw(rc);
	}
}