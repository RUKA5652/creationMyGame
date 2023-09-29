#include "GameUIDraw.h"
#include "../GameDrawIndex.h"
#include"../../../Base/GameCore.h"
#include"../../../osu/Skin/FolderSearch.h"
#include"../Key/KeyData.h"
#include "../../../WindowSize.h"
#include "../../../../AnimCurve/animCurve.h"

GameUIDraw::GameUIDraw(LaneDivisionConstPtr division, DecisionTransformConstPtr data)
{
	Init(division, data);
}

GameUIDraw::~GameUIDraw()
{
	for (auto& [key, handle] : keyHandle_)
	{
		DeleteGraph(handle);
	}
	DeleteGraph(screen_);
}

void GameUIDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	if (startPoint_ == 0) [[unlikely]]
	{
		startPoint_ = delta ;
	}
	else if (changeDelta_) [[unlikely]]
	{
		float time = static_cast<float>(delta - startPoint_) / -startPoint_;
		changeDelta_ = ReBaseCurve(time, 5.0f);

		if (time >= 1.0f)
		{
			changeDelta_ = std::nullopt;
		}
	}




}

void GameUIDraw::Draw()
{
	if (changeDelta_) [[unlikely]]
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA,255 * (1 - static_cast<int>(changeDelta_.value())));
		DrawGraph(0, 0, screen_, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}	

void GameUIDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::KeyGuid), shared_from_this());
}

void GameUIDraw::Init(LaneDivisionConstPtr& division, DecisionTransformConstPtr& data)
{
	FolderSearch(std::bind_front(&GameUIDraw::LoadKeyHandle,this))("resource/skin/UI/Key");
	//•`‰æƒf[ƒ^ì¬
	auto& boxVec = division->GetBoxVec();
	SetPlayKey(division);
	auto& windowSize = lpWindowSize->GetSize();
	screen_ = MakeScreen(windowSize.x, windowSize.y, true);
	auto inScreen = GetDrawScreen();
	SetDrawScreen(screen_);
	for (int i = 0; i < static_cast<int>(boxVec.size());i++)
	{
		int x, y;
		GetGraphSize(playKeyHandle_[i], &x, &y);
		auto size = boxVec[i].RB.x - boxVec[i].LT.x ;
		size = (size - x) / 2;
		DrawGraph(boxVec[i].LT.x + size, data->GetOffset() - y,playKeyHandle_[i],true);

	}
	SetDrawScreen(inScreen);


	startPoint_ = 0;
	changeDelta_ = 1;
}

void GameUIDraw::LoadKeyHandle(const std::filesystem::path& path, std::string&& name)
{
	keyHandle_.emplace(name, LoadGraph(path.string().c_str()));
}

void GameUIDraw::SetPlayKey(LaneDivisionConstPtr& division)
{
	auto data = KeyData()(division->divisionData);
	playKeyHandle_.resize(data.size());
	playKeyHandle_.shrink_to_fit();
	for (int i = 0 ;i < static_cast<int>(data.size());i++)
	{
		playKeyHandle_[i] = keyHandle_[data[i].first];
	}


}
