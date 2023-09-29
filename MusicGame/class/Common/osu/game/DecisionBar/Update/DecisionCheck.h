#pragma once
#include <map>
#include "../../DecisionData.h"
#include "../../../../../Input/InputManager.h"
#include "../HitAnim/HitAnimEnum.h"
#include"../SetDrawEnum.h"
#include"../../../Skin/Sound/SkinSoundData.h"
#include"../Sound/HitSoundData.h"

/// <summary>
/// �m�[�c������N���X
/// </summary>
class DecisionCheck
{
public:
	DecisionCheck(Beat::CheckHitTime& hitTime,const Decision::HitSoundCustomSet& soundData,
		TimingPoints::iterator& nowTimingPoint, Beat::SampleSet defSampleSet, ScoreMagDataPtr score);
	virtual ~DecisionCheck();
	/// <summary>
	/// �X�V���\�b�h
	/// </summary>
	/// <param name="inputResult">�L�[���͌���</param>
	/// <param name="laneNo">�������肽�����[���ԍ�</param>
	/// <param name="nowTime">���݂̐i�s����</param>
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

