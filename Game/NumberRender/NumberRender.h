#pragma once
	enum class NumberColor
	{
		Black,/** 黒駒側の数字(Number_*)*/
		White,/** 白駒側の数字(WhiteNumber_*)*/
	};

class NumberRender
{
public:
	NumberRender();
	~NumberRender();

	bool Init(NumberColor color, float digitWidth, float digitHeight);

	/** number:表示したい数値 / x,y: 一番左の桁の描画位置 / spacing : 桁の間隔*/
	void Draw(RenderContext& rc, int number, float x, float y, float spacing);

private:
	/** 数字のスプライトレンダラー*/
	SpriteRender m_digitSpriteRender[10];
};

