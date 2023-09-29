#include "Draw.h"
#include"../../Base/GameCore.h"
#include"DrawIndex.h"
#include"../game/Lane/Draw/ObliqueLaneDraw.h"
#include"../game/HitObj/NotesDraw.h"
#include "../game/HitObj/CreateNotes.h"
#include"../game/HitObj/GetPriorTime.h"
#include"../game/DecisionBar/DecisionBarDraw.h"
#include"../Skin/Image/SkinImage.h"
#include "../../WindowSize.h"
#include"../../../JsonParam/IOJSON.h"

/// <summary>
/// JSONで使用するデータ
/// </summary>
inline namespace JSON
{
	//ファイル名前
	constexpr const char* FileName = "SpeedAdjust";
	//キー
	constexpr const char* Image = "Image";
}


SpeedAdjustDraw::SpeedAdjustDraw(Notes::Initialization* init)
	:numImage_(lpSkinImagePtr.GetAllImage(Beat::SkinImageType::num))
{
	lane_ = new ObliqueLaneDraw(init->division);

	GetGraphSize(numImage_[0], &numImageSize_.x, &numImageSize_.y);

	division_ = init->division;
	decisionData_ = init->decisionData;
	notesData_ = init->noteData;
	note_ = new NotesDraw(init->division, init->noteData , init->noteSize, init->hitdata);

	bar_ = new DecisionBarDraw(init->division,decisionData_);


	speedImage_ = LoadGraph("resource/skin/UI/Speed/Speed.png");
	GetGraphSize(speedImage_, &speedSize_.x, &speedSize_.y);
}

SpeedAdjustDraw::~SpeedAdjustDraw()
{
	delete lane_;
	delete bar_;
	delete note_;
	DeleteGraph(speedImage_);
}

void SpeedAdjustDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{

}

void SpeedAdjustDraw::Draw()
{
	//int blendMode,blendParam;
	//GetDrawBlendMode(&blendMode,&blendParam);
	LaneDraw();
	DrawNum();
	//SetDrawBlendMode(blendMode, blendParam);
}

void SpeedAdjustDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(SpeedAdjustDrawIndex::Lane), shared_from_this());
}

void SpeedAdjustDraw::LaneDraw()
{
	lane_->SetScreen();
	lane_->DrawLane();
	bar_->Draw();
	note_->Draw();
	lane_->DrawOblique();
}

void SpeedAdjustDraw::DrawNum()
{
	auto& winSize = lpWindowSize->GetSize();

	auto exSize = static_cast<float>(numImageSize_.y)/speedSize_.y;

	Vector2 spSize = (speedSize_.cast<float>() * exSize).cast<int>();

	auto offsetX = (division_->GetBothEnds().front - spSize.x) / 2;
	auto offsetY = (winSize.y - numImageSize_.y) / 2;

	DrawExtendGraph(offsetX , offsetY,offsetX + spSize.x, offsetY + spSize.y,speedImage_,true);

	auto numData = lpConfigData->GetConfigData().ManiaSpeed;
	int size = 1;
	for (int i = 10; numData % i != numData; i *= 10)
	{
		size++;
	}
	int cnt = 0;

	auto offset = offsetX + spSize.x;
	for (int num = numData % 10; cnt < size; numData /= 10, num = numData % 10)
	{
		DrawGraph(offset + numImageSize_.x * (size - ++cnt) /*ずらす量*/, offsetY, numImage_[num], true);
	}





}

void SpeedAdjustDraw::Load()
{
	//JSONデータ読み込み
	auto result = InPutJSON()(FileName);
	//格納
	if (result)
	{
		auto& doc = result.value();
		speedImage_ = LoadGraph(doc[Image].GetString());
	}
}
