#pragma once
#include <map>
#include "../../DecisionData.h"
#include "../../../../../Input/InputManager.h"
#include "../HitAnim/HitAnimEnum.h"
#include"../SetDrawEnum.h"
#include"../../../Skin/Sound/SkinSoundData.h"
#include"../Sound/HitSoundData.h"

/// <summary>
/// ノーツ判定基底クラス
/// </summary>
class DecisionCheck
{
public:
	DecisionCheck(Beat::CheckHitTime& hitTime,const Decision::HitSoundCustomSet& soundData,
		TimingPoints::iterator& nowTimingPoint, Beat::SampleSet defSampleSet, ScoreMagDataPtr score);
	virtual ~DecisionCheck();
	/// <summary>
	/// 更新メソッド
	/// </summary>
	/// <param name="inputResult">キー入力結果</param>
	/// <param name="laneNo">判定を取りたいレーン番号</param>
	/// <param name="nowTime">現在の進行時間</param>
	/// <param name="notesData"></param>
	/// <param name="hitsData"></param>
	/// <param name="func"></param>
	/// <param name="drawFunc"></param>
	virtual void Update(const InputManager::InputResult* inputResult, int laneNo, const Beat::Time& nowTime,
		Note::NotesDataConstPtr& notesData, Beat::HitsDataPtr& hitsData, Decision::AnimSetFunc& func, Decision::SetDrawFunc& drawFunc) = 0;

protected:
	const Decision::HitSoundCustomSet& soundData_;

	Beat::CheckHitTime& checkHitTime_;

	TimingPoints::iterator& nowTimingPoint_;

	Beat::SampleSet defSampleSet_;

	ScoreMagDataPtr score_;

	virtual bool CheckHitKey(const InputManager::InputResult* inputResult, int laneNo);

	void SoundPlay(const Beat::Sound::Type& type);

	void ConboCount(Beat::HitsDataPtr& hitsData, Beat::HitResult::Type type);

};

