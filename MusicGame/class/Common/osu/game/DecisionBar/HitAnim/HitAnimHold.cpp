#include "HitAnimHold.h"
#include"../../../Skin/Image/SkinImage.h"
#include"../../../../../Manager/ImageMng.h"
#include"../../../../../shaderDraw/DxShDraw.h"
#include"../../../../WindowSize.h"
#include"../CreateBarBoxData.h"


HitAnimHold::HitAnimHold(LaneDivisionConstPtr division, DecisionTransformConstPtr transform)
{
	barBox_ = CreateBarBoxData()(division, transform);
	size_ = barBox_[0].RB - barBox_[0].LT;
	HandleSetUp();
}

HitAnimHold::~HitAnimHold()
{
	for (auto& data : handle_)
	{
		lpSkinImagePtr.DeletAnimHandle(data.handle);
	}
}

void HitAnimHold::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	for (auto& data : handle_)
	{
		if (!data.animFlag)
		{
			continue;
		}
		if (lpSkinImagePtr.Update(data.handle, delta))
		{
			lpSkinImagePtr.Reset(data.handle);
		}
	}
}

void HitAnimHold::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	int x, y;
	for (auto& [handle, pos,flag] : handle_)
	{
		if (!flag)
		{
			continue;
		}
		auto image = lpSkinImagePtr.GetImageHandle(handle);
		GetGraphSize(image, &x, &y);
		DrawGraph(pos.x - x / 2, pos.y - y / 2, image, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void HitAnimHold::SetAnim(int index, bool flag)
{
	if (handle_[index].animFlag)
	{
		handle_[index].animFlag = flag;
		return;
	}
	Vector2 pos = barBox_[index].LT;
	pos += size_ / 2;
	handle_[index].pos = pos;
	handle_[index].animFlag = flag;
	
}

void HitAnimHold::SetFunc(GameCore* gameCore)
{
}

void HitAnimHold::HandleSetUp()
{
	handle_.resize(barBox_.size());
	handle_.shrink_to_fit();
	for (auto& data : handle_)
	{
		data.handle = lpSkinImagePtr.GetAnimHandle(Beat::SkinImageType::HoldLighth);
		data.pos = { 0,0 };
		data.animFlag = false;
	}
}
