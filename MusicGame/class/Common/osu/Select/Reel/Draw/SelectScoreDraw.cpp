#include "SelectScoreDraw.h"
#include "../../SelectDrawIndex.h"
#include"../../../../Base/GameCore.h"
#include"../../../../template/Vector2.h"
#include "../../../../WindowSize.h"
#include "../../../Skin/Image/SkinImage.h"
#include "../../../../../shaderDraw/DxShDraw.h"


namespace
{
	constexpr Timer::DeletaTime Wait = 1000;

}


SelectScoreDraw::SelectScoreDraw(Beat::ReelDataPtr reelData)
	:numImage_(lpSkinImagePtr.GetAllImage(Beat::SkinImageType::num))
{
	//オフセット　ランキング描画データ作成
	rankingDraw_ = LoadGraph("resource/skin/UI/Select/ranking.png");
	GetGraphSize(rankingDraw_, &rankGrapSize_.x, &rankGrapSize_.y);
	auto& winSize = lpWindowSize->GetSize();
	GetGraphSize(numImage_[0], &numImageSize_.x, &numImageSize_.y);
	offsetPos_.x = 0;
	offsetPos_.y = (winSize.y - ScoreConstantData::Max * numImageSize_.y - rankGrapSize_.y)/2;


	//数値描画データ作成
	reelData_ = reelData;	
	if (reelData_->mainSortIndex_ &&
		reelData_->mapGroupIndex_)
	{
		const auto& path = reelData_->GetMapData()->path;
		score_ = loadFunc_.Load(nowDrawPath_);
		nowDrawPath_ = path;
	}
	state_ = State::Non;
	waitTime_ = 0;

	drawScreen_ = MakeScreen(winSize.x, winSize.y,true);
	maxCnt_ = 1;
	for (int i = 10; Beat::maxScore % i != Beat::maxScore; i *= 10)
	{
		maxCnt_++;
	}

	//数値内時よう描画データ作成
	noDataImage_ = LoadGraph("resource/skin/UI/Select/noData.png");
	GetGraphSize(noDataImage_, &noDataDrawPos_.x, &noDataDrawPos_.y);
	noDataDrawPos_.x = (rankGrapSize_.x - noDataDrawPos_.x)/2;
	noDataDrawPos_.x = noDataDrawPos_.x >= 0 ? noDataDrawPos_.x : noDataDrawPos_.x * -1;
	noDataDrawPos_.y = offsetPos_.y + (ScoreConstantData::Max * numImageSize_.y - noDataDrawPos_.y) / 2;


}

SelectScoreDraw::~SelectScoreDraw()
{
	DeleteGraph(drawScreen_);
	DeleteGraph(noDataImage_);
	DeleteGraph(rankingDraw_);
}

SelectScoreDraw::DrawLoadPrm::DrawLoadPrm()
{
	auto& winSize = lpWindowSize->GetSize();
	screen = MakeScreen(winSize.x, winSize.y, true);
	shaderHndle = LoadPixelShader("resource/shader/CoreThickness.pso");
	mainTex = LoadGraph("resource/skin/UI/Select/mainTex.png");
	thickTex = LoadGraph("resource/skin/UI/Select/loadMask.png");

	buffHandle = CreateShaderConstantBuffer(sizeof(float) * 4);

	thicknessMax = 0;
	thicknessMin = 0;
}

SelectScoreDraw::DrawLoadPrm::~DrawLoadPrm()
{
	DeleteShader(shaderHndle);
	DeleteGraph(mainTex);
	DeleteGraph(thickTex);
	DeleteGraph(screen);
	DeleteShaderConstantBuffer(buffHandle);

}

void SelectScoreDraw::DrawLoadPrm::Update(Timer::DeletaTimeConst& delta)
{
	thicknessMax += delta/1000.0f;
	while(thicknessMax > 1.0f)
	{
		thicknessMax -= 1.0f;
	}
	thicknessMin = thicknessMax - 0.3f;
	if (thicknessMin < 0)
	{
		thicknessMin = 1 + thicknessMin;
	}


}


void SelectScoreDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	if (state_ == State::Selet)
	{
		drawLoadPrm_.Update(delta);
		waitTime_ += delta;
		if (waitTime_ >= Wait)
		{
			waitTime_ = 0;
		}
	}

	LoadData();

}

void SelectScoreDraw::Draw()
{
	DrawGraph(0, offsetPos_.y, rankingDraw_, true);
	if (state_ != State::Non)
	{
		DrawLoad();
		return;
	}
	DrawGraph(0, 0, drawScreen_, true);
}

void SelectScoreDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(SelectDrawIndex::Score), shared_from_this());
}

void SelectScoreDraw::DrawScore()
{
	auto inScreen = GetDrawScreen();
	SetDrawScreen(drawScreen_);
	ClearDrawScreen();
	if (score_.size())
	{
		DrawNo();
	}
	else
	{
		DrawNonData();
	}


	SetDrawScreen(inScreen);
}

void SelectScoreDraw::DrawNo()
{
	for (int i = 0; i < score_.size(); i++)
	{
		auto numData = score_[i];
		int size = 1;
		for (int i = 10; numData % i != numData; i *= 10)
		{
			size++;
		}
		int cnt = 1;
		int offsetY = rankGrapSize_.y + offsetPos_.y;
		for (int num = numData % 10; cnt <= maxCnt_; numData /= 10, num = numData % 10, ++cnt)
		{
			int index = num;
			if (cnt > size)
			{
				num = 0;
			}

			DrawGraph(offsetPos_.x + numImageSize_.x * (maxCnt_ - cnt) /*ずらす量*/, offsetY + numImageSize_.y * i, numImage_[index], true);
		}
		auto result = makeRank_(score_[i]);
		DrawGraph(offsetPos_.x + numImageSize_.x * maxCnt_ /*ずらす量*/, offsetY + numImageSize_.y * i, result.first[1], true);
	}

}

void SelectScoreDraw::DrawNonData()
{
	DrawGraph(noDataDrawPos_.x, noDataDrawPos_.y, noDataImage_, true);
}

void SelectScoreDraw::LoadData()
{
	if (reelData_->mainSortIndex_ &&
		reelData_->mapGroupIndex_)
	{
		const auto& path = reelData_->GetMapData()->filePath;
		if (path == nowDrawPath_ && state_ == State::Selet && waitTime_ == 0)
		{
			score_  = loadFunc_.Load(nowDrawPath_);
			state_ = State::Non;
			DrawScore();
		}
		if (path != nowDrawPath_)
		{
			state_ = State::Selet;
			nowDrawPath_ = path;
			waitTime_ = 0;
		}
	}
}

void SelectScoreDraw::DrawLoad()
{
	auto inScreen = GetDrawScreen();

	SetDrawScreen(drawLoadPrm_.screen);
	ClearDrawScreen();

	DxShDraw::DrawGraph(0,offsetPos_.y + rankGrapSize_.y , drawLoadPrm_.mainTex, [&]() {
		SetUsePixelShader(drawLoadPrm_.shaderHndle);
	SetUseTextureToShader(0, drawLoadPrm_.mainTex);
	SetUseTextureToShader(1, drawLoadPrm_.thickTex);
	auto buff = static_cast<float*>(GetBufferShaderConstantBuffer(drawLoadPrm_.buffHandle));
	buff[0] = drawLoadPrm_.thicknessMax;
	buff[1] = drawLoadPrm_.thicknessMin;
	UpdateShaderConstantBuffer(drawLoadPrm_.buffHandle);
	SetShaderConstantBuffer(drawLoadPrm_.buffHandle, DX_SHADERTYPE_PIXEL, 0);
		});
	printf("max%fmin%f\n", drawLoadPrm_.thicknessMax, drawLoadPrm_.thicknessMin);
	SetDrawScreen(inScreen);
	DrawGraph(0, 0, drawLoadPrm_.screen, true);
}

