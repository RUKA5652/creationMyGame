#pragma once
#include"../../../Base/Update/UpdateBase.h"
#include"../HitObj/NoteData.h"
#include"../DecisionData.h"
#include"../DecisionTransform.h"
#include"../../../../Input/InputManager.h"
#include"HitAnim/HitAnimEnum.h"
#include"Update/DecisionCheck.h"
#include"SetDrawEnum.h"
#include"Sound/HitSoundData.h"

class DecisionTransform;
/// <summary>
/// ”»’è‚ðŽæ‚éƒNƒ‰ƒX
/// </summary>
class DecisionUpdate
	:public UpdateBase
{
public:
	DecisionUpdate(Beat::HitsDataPtr hitsData,DecisionTransformConstPtr data, 
		Note::NotesDataConstPtr notesData, Beat::LoadDataCPtr loadData,
		std::shared_ptr<Decision::AnimSetFunc> animSetFunc, Decision::SetDrawFuncPtr drawSetFunc);
	~DecisionUpdate();
	void Update(Timer::DeletaTimeConst& delta,const InputManager& input) override;

	void DebugDraw();

private:

	Note::NotesDataConstPtr notesData_;
	Beat::HitsDataPtr hitsData_;

	std::shared_ptr<Decision::AnimSetFunc> setAnim_;
	Decision::SetDrawFuncPtr drawSetFunc_;

	Beat::Time limitTime_;

	Beat::CheckHitTime checkHitTime_;

	TimingPointsPtr timingPointsPtr_;

	TimingPoints::iterator nowTimingPoint_;

	std::array<std::unique_ptr<DecisionCheck>, 2> check_;

	Decision::HitSoundCustomSet soundData_;

	void LoadLimitTime();

	void SetCheckHitTime();

	void SetCheckClass(Beat::LoadDataCPtr& loadData);

	void CreateSoundData(Beat::LoadDataCPtr& loadData);

};

