#include "LightDraw.h"
#include"../../Skin/Image/SkinImage.h"
#include"../DecisionTransform.h"
#include"../Lane/LaneDivision.h"
#include"../../../Base/GameCore.h"
#include "../GameDrawIndex.h"
#include "../../../../Input/Game/GameSceneInputKey.h"
#include "../../../../Input/EnumCast.h"


LightDraw::LightDraw(LaneDivisionConstPtr division, DecisionTransformConstPtr data)
{
	division_ = division;
	CreatePos(data);
	LoadImageData();
	inputData_ = nullptr;
}

void LightDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	inputData_ = &input.GetInputData();
}

void LightDraw::Draw()
{
	if (!inputData_)
	{
		return;
	}

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	auto& box = division_->GetBoxVec();
	for (int i = 0; i < box.size();i++)
	{
		auto key = &inputData_->at(i);
		if (inputData_->at(i).now)
		{
			DrawExtendGraph(box[i].LT.x, 0, box[i].RB.x, EndPosY_, image_, true);
		}
	}
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void LightDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::Light), shared_from_this());
}

void LightDraw::LoadImageData()
{
	image_ = lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::LaneLighth);
}

void LightDraw::CreatePos(DecisionTransformConstPtr& data)
{
	EndPosY_ = data->GetOffset() + data->GetSize().y;
}
