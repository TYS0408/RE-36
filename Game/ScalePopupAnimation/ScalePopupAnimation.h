#pragma once
class ScalePopupAnimation
{
public:
	ScalePopupAnimation() {};
	~ScalePopupAnimation() {};

	bool Update(float deltaTime);
	bool Start();

public:
	enum class State
	{
		Idle,
		ScaleUp,
		Hold,
		ScaleOut,
	};
	/** targetScale : 最終的に到達させたいスケール(通常は1.0f)*/
	/** holdTime : 等倍で制止する秒数*/
	/** lerpSpeed : 目標値に近づく速さ(0.0～1.0)大きいほど早く到達する*/
	/** reachThreShold : 「十分近づいた」とみなす誤差のしきい値*/
	void Init(float targetScale, float holdTime, float lerpSpeed, float reachThreShold = 0.01f);

	float GetScale()const
	{
		return m_scale;
	}
	/** アニメーションが再生中かどうかを返す */
	bool IsPlaying()const
	{
		return m_state != State::Idle;
	}
	/** 現在のアニメーション状態を返す */
	State GetState()const
	{
		return m_state;
	}

private:
	State m_state = State::Idle;
	float m_scale = 0.0f;
	float m_holdTimer = 0.0f;

	float m_targetScale = 1.0f;
	float m_holdTime = 0.0f;
	float m_lerpSpeed = 0.1f;
	float m_reachThreshold = 0.01f;
};

