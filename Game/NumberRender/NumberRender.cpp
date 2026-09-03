#include "stdafx.h"
#include "NumberRender.h"
namespace 
{
	/** 黒駒側の数字のファイルパス*/
	const char* BLACK_NUMBER_FILEPATH[10] =
	{
			"Assets/Sprite/OseroNumber/Number_Zero.dds",
			"Assets/Sprite/OseroNumber/Number_One.dds",
			"Assets/Sprite/OseroNumber/Number_Two.dds",
			"Assets/Sprite/OseroNumber/Number_Three.dds",
			"Assets/Sprite/OseroNumber/Number_Four.dds",
			"Assets/Sprite/OseroNumber/Number_Five.dds",
			"Assets/Sprite/OseroNumber/Number_Six.dds",
			"Assets/Sprite/OseroNumber/Number_Seven.dds",
			"Assets/Sprite/OseroNumber/Number_Eight.dds",
			"Assets/Sprite/OseroNumber/Number_Nine.dds"
	};
	/** 白駒側の数字のファイルパス*/
	const char* WHITE_NUMBER_FILEPATH[10] =
	{
			"Assets/Sprite/OseroNumber/WhiteNumber_Zero.dds",
			"Assets/Sprite/OseroNumber/WhiteNumber_One.dds",
			"Assets/Sprite/OseroNumber/WhiteNumber_Two.dds",
			"Assets/Sprite/OseroNumber/WhiteNumber_Three.dds",
			"Assets/Sprite/OseroNumber/WhiteNumber_Four.dds",
			"Assets/Sprite/OseroNumber/WhiteNumber_Five.dds",
			"Assets/Sprite/OseroNumber/WhiteNumber_Six.dds",
			"Assets/Sprite/OseroNumber/WhiteNumber_Seven.dds",
			"Assets/Sprite/OseroNumber/WhiteNumber_Eight.dds",
			"Assets/Sprite/OseroNumber/WhiteNumber_Nine.dds"
	};
}

NumberRender::NumberRender()
{

}

NumberRender::~NumberRender()
{

}

bool NumberRender::Init(NumberColor color, float digitWidth, float digitHeight)
{
	/** 数字のスプライトレンダラーがブラックだったら黒い駒を描画*/
	const char** filepaths = (color == NumberColor::Black) ? BLACK_NUMBER_FILEPATH : WHITE_NUMBER_FILEPATH;

	for (int i = 0; i < 10; i++)
	{
		m_digitSpriteRender[i].Init(filepaths[i], digitWidth, digitHeight);
	}
		return true;
}


void NumberRender::Draw(RenderContext& rc, int number, float x, float y, float spacing)
{
	/**負の数をガード*/
	if (number < 0) number = 0;

	/** 2桁の分解*/
	int digits[8];
	int digitCount = 0;
	int temp = number;
	if (temp == 0)
	{
		digits[digitCount++] = 0;
	}

	/** 各桁の数字を取得 */
	while (temp > 0 && digitCount < 8)
	{
		/** ここで10で割った数の余りを取得*/
		 /** 例: 24 % 10 = 4 */
		digits[digitCount++] = temp % 10;
		/** ここでは10で割った数を取得*/
		/** 例: 24 / 10 = 2 */
		temp /= 10;
	}

	/** 数字全体の横幅を求めて、中心がxになるように開始位置を左にずらす*/
	float totalWidth = spacing * (digitCount - 1);
	float startX = x - totalWidth * 0.5f;
	for (int i = digitCount - 1; i >= 0; i--)
	{
		m_digitSpriteRender[digits[i]].SetPosition(Vector3{startX,y,0.0f});
		m_digitSpriteRender[digits[i]].Update();
		m_digitSpriteRender[digits[i]].Draw(rc);
		startX += spacing;
	}
}