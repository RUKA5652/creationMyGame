#pragma once
#include"../../Base/Draw/DrawBase.h"
#include"../game/HitObj/NoteData.h"
#include"../game/DecisionTransform.h"
#include"../game/HitObj/Notes.h"
#include"../Skin/Image/SkinImageData.h"

class ObliqueLaneDraw;
class NotesDraw;
class DecisionBarDraw;
/// <summary>
/// スピード設定描画
/// </summary>
class SpeedAdjustDraw
	:public DrawBase
{
public:
	SpeedAdjustDraw(Notes::Initialization* init);
	~SpeedAdjustDraw();

	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
	void Draw() override;

private:
	void SetFunc(GameCore* gameCore) override;

	void LaneDraw();

	void DrawNum();

	void Load();

	Timer::DeletaTime nowTime_;

	const std::vector<Beat::SkinImage>& numImage_;

	Vector2 numImageSize_;

	int speedImage_;

	Vector2 speedSize_;

	ObliqueLaneDraw* lane_;
	NotesDraw* note_;
	DecisionBarDraw* bar_;

	LaneDivisionConstPtr division_;
	Note::NotesDataPtr notesData_;
	DecisionTransformPtr decisionData_;
};

