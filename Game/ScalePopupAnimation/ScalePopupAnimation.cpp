#include "stdafx.h"
#include "ScalePopupAnimation.h"


void ScalePopupAnimation::Init(float targetScale, float holdTime, float lerpSpeed, float reachThreShold)
{
	m_targetScale = targetScale;
	m_holdTime = holdTime;
	m_lerpSpeed = lerpSpeed;
	m_reachThreshold = reachThreShold;
}

bool ScalePopupAnimation::Start()
{
	/** 最初はScaleUpから始める*/
	m_state = State::ScaleUp;
	m_scale = 0.0f;
	m_holdTimer = 0.0f;
	return true;

}


bool ScalePopupAnimation::Update(float deltaTime)
{
	bool finishedThisFrame = false;

	switch (m_state)
	{
	case State::ScaleUp:
		{
		/** 目標スケールに向かって近づける*/
		m_scale += (m_targetScale - m_scale) * m_lerpSpeed;

		if(fabsf(m_targetScale - m_scale) < m_reachThreshold)
		{
			m_scale = m_targetScale;
			m_state = State::Hold;
			m_holdTimer = 0.0f;
		}
		break;
		}

	case State::Hold:
	{
		m_holdTimer += deltaTime;
		if (m_holdTimer >= m_holdTime)
		{
			m_state = State::ScaleOut;
		}
		break;
	}

	case State::ScaleOut:
	{
		/** 0に向かって少しずつ縮める*/
		m_scale += (0.0f - m_scale) * m_lerpSpeed;
		if (fabsf(m_scale) < m_reachThreshold)
		{
			m_scale = 0.0f;
			m_state = State::Idle;
			finishedThisFrame = true;
		}
		break;
	}
	default:
		break;
	}
	return finishedThisFrame;
}