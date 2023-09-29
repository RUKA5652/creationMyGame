#pragma once
#include"../../Base/Update/UpdateBase.h"
#include"../game/HitObj/NoteData.h"
#include"../game/DecisionTransform.h"
#include "../game/HitObj/CreateNotes.h"

/// <summary>
/// スピード設定　更新処理
/// </summary>
class SpeedAdjustUpdate
	:public UpdateBase
{
public:
	SpeedAdjustUpdate(Notes::Initialization* init);
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;

private:

	Note::NotesDataPtr notesData_;
	DecisionTransformPtr decisionData_;
	LaneDivisionConstPtr division_;


	std::array<int,4> endTime_;

	Timer::DeletaTime nowTime_;

	int& speed_;

	float noteTime_;

	void CreateEndTime();

	void CreateNote();

	void Load();
};

