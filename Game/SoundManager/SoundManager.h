#pragma once
#include "sound/SoundSource.h"

enum enSound
{
	enSound_GameBGM_1,
	enSound_GameBGM_2,
	enSound_GameBGM_3,
	enSound_PutStone,
	enSound_Pass,
	enSound_Num
};

class SoundManager : public IGameObject
{
public:
	SoundManager();
	~SoundManager() {};
	///<summary>
	///指定したサウンドを再生し、再生中のサウンドソースを返します。
	/// </summary>
	/// <param name="number">再生するサウンドを指定します。</param>
	/// <param name="isLoop">サウンドをループ再生するかどうかをしていします。デフォルトは true です。</param>
	/// <param name="volume">再生音量を指定します。デフォルトは1.0fです。</param>
	/// <returns>再生中のサウンドソースへのポインタ。</returns>
	SoundSource* PlayingSound(enSound number, bool isLoop = true, float volume = 1.0f);
};

