#include "HitAnimNormal.h"
#include"../../../Skin/Image/SkinImage.h"
#include"../../../../../Manager/ImageMng.h"
#include"../../../../../shaderDraw/DxShDraw.h"
#include"../../../../WindowSize.h"
#include"../CreateBarBoxData.h"


HitAnimNormal::HitAnimNormal(LaneDivisionConstPtr division, DecisionTransformConstPtr transform)
{
	barBox_ = CreateBarBoxData()(division, transform);
	size_ = barBox_[0].RB - barBox_[0].LT;
}

HitAnimNormal::~HitAnimNormal()
{
	for (auto& data : handle_)
	{
		lpSkinImagePtr.DeletAnimHandle(data.handle);
	}
	for (auto& data : poolHandle_)
	{
		lpSkinImagePtr.DeletAnimHandle(data.handle);
	}
}

void HitAnimNormal::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	for (auto& data : handle_)
	{
		if (lpSkinImagePtr.Update(data.handle, delta))
		{
			lpSkinImagePtr.Reset(data.handle);
			poolHandle_.emplace_back(handle_[0]);
			handle_.pop_front();
		}
	}
}

void HitAnimNormal::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);

	int x, y;
	for (auto& [handle, pos] : handle_)
	{
		auto image = lpSkinImagePtr.GetImageHandle(handle);
		GetGraphSize(image, &x, &y);
		DrawGraph(pos.x - x / 2, pos.y - y / 2, image, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void HitAnimNormal::SetAnim(int index, bool flag)
{
	Vector2 pos = barBox_[index].LT;
	pos += size_ / 2;


	if (poolHandle_.size() == 0)
	{
		handle_.emplace_back(lpSkinImagePtr.GetAnimHandle(Beat::SkinImageType::NotesLighth), pos);
		return;
	}
	auto& setData = poolHandle_[0];
	setData.pos = pos;
	handle_.emplace_back(std::move(setData));
	poolHandle_.pop_front();
}

void HitAnimNormal::SetFunc(GameCore* gameCore)
{
}
