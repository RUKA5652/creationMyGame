#include "ResultDraw.h"
#include <DxLib.h>
#include"../../Base/GameCore.h"
#include "../../../Manager/ImageMng.h"
#include "../../WindowSize.h"
#include"../Skin/Image/SkinImage.h"
#include"../../../shaderDraw/DxShDraw.h"
#include"../../../AnimCurve/animCurve.h"
#include <filesystem>

constexpr Timer::DeletaTime maxTime = 160;
constexpr Timer::DeletaTime MaxRankTime = 1500;

constexpr float RankExSize = 3.0f;

ResultDraw::ResultDraw(const std::string& filePass, Beat::ResultDataConstPtr result, ResultSharingDataConstPtr sharData)
{
	sharData_ = std::move(sharData);
	result_ = result;
	time_ = 0;
	rankTime_ = 0;

	std::filesystem::path pass = filePass;
	pass.replace_filename(result->image->filePass);
	backImage_ = lpImageMng.GetID(pass.string())[0];
	pos_.x = result->image->xOffset;
	pos_.y = result->image->yOffset;
	score_ = static_cast<int>(std::round(result->hitsData->score));

	shaderHandle_ = LoadPixelShader("resource/shader/UVScroll.pso");
	subImage_ = LoadGraph("resource/skin/Default/subImage.png");
	CreateNumImage();
	auto& winSize = lpWindowSize->GetSize();
	resultImage_ = MakeScreen(winSize.x, winSize.y, true);
	CreateResultImage(result);
}

ResultDraw::~ResultDraw()
{
	DeleteGraph(resultImage_);
	DeleteGraph(resultImage_);
	DeleteShader(shaderHandle_);
}

void ResultDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	if (rankTime_ <= MaxRankTime)
	{
		rankTime_ += delta;
	}
	for (auto& select : sharData_->selects)
	{
		if (select->blendParam == 1)
		{
			lpSkinImagePtr.Update(select->image, delta);
		}
		else
		{
			lpSkinImagePtr.SetStart(select->image);
		}
	}
	time_ += delta;
	if (time_ >= maxTime)
	{
		time_ = 0;
	}

}

void ResultDraw::Draw()
{
	DrawBackImage();
	CreateResultImage(result_);
	DrawGraph(0, 0, resultImage_, true);
	RankDraw();
	SelectsDraw();
}

void ResultDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(0, shared_from_this());
}

void ResultDraw::DrawBackImage()
{

	auto& winSize = lpWindowSize->GetSize();
	int grapX, grapY;
	GetGraphSize(backImage_, &grapX, &grapY);
	auto ratioX = winSize.x / static_cast<float>(grapX);
	auto ratioY = winSize.y / static_cast<float>(grapY);
	auto ratio = static_cast<int>(max(ratioX, ratioY));
	WindowSize::Size center = { winSize.x / 2, winSize.y / 2 };
	grapX *= ratio;
	grapY *= ratio;
	grapX /= 2;
	grapY /= 2;
	DrawExtendGraph(center.x - grapX, center.y - grapY,
		center.x + grapX, center.y + grapY, backImage_, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawBox(0, 0, winSize.x, winSize.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void ResultDraw::RankDraw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0,
		lpWindowSize->GetSize().x, sharData_->rank.pos.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawGraph(sharData_->rank.pos.x, 0, lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::Rank), true);


	auto exSize = std::lerp(RankExSize, 1.0f, ReBaseCurve(rankTime_ * 2/ static_cast<float>(MaxRankTime)*1/2, 8));
	float sizeX, sizeY;
	GetGraphSizeF(sharData_->rank.rankImage, &sizeX, &sizeY);
	sizeX /= 2;
	sizeY /= 2;
	auto pos = sharData_->rank.pos;
	pos.x += static_cast<int>(sizeX);
	pos.y += static_cast<int>(sizeY);
	sizeX *= exSize;
	sizeY *= exSize;
	DrawExtendGraph(pos.x - static_cast<int>(sizeX), pos.y - static_cast<int>(sizeY), pos.x + static_cast<int>(sizeX), pos.y + static_cast<int>(sizeY), sharData_->rank.rankImage, true);

}

void ResultDraw::MakePoly(Vector2 pos,int sizeX,int sizeY)
{
	for (auto& d : polyData_)
	{
		d.rhw = 1.0f;
		d.dif = GetColorU8(0xff, 0xff, 0xff, 0xff);
		d.spc = GetColorU8(0x00, 0x00, 0x00, 0x00);
		d.pos.z = 0.0f;
	}
	Vector2Flt posf = pos.cast<float>();
	polyData_[0].pos.x = posf.x ;
	polyData_[0].pos.y = posf.y ;
	polyData_[0].u = 0;
	polyData_[0].v = 0;
	polyData_[0].su = 0;
	polyData_[0].sv = 0;

	polyData_[1].pos.x = posf.x + sizeX;
	polyData_[1].pos.y = posf.y;
	polyData_[1].u = 1;
	polyData_[1].v = 0;
	polyData_[1].su = 1;
	polyData_[1].sv = 0;

	polyData_[2].pos.x = posf.x ;
	polyData_[2].pos.y = posf.y + sizeY;
	polyData_[2].u = 0;
	polyData_[2].v = 1;
	polyData_[2].su = 0;
	polyData_[2].sv = 1;

	polyData_[3].pos.x = posf.x + sizeX;
	polyData_[3].pos.y = posf.y + sizeY;
	polyData_[3].u = 1;
	polyData_[3].v = 1;
	polyData_[3].su = 1;
	polyData_[3].sv = 1;

	auto t = 1.0f - static_cast<float>(time_) / static_cast<float>(maxTime);
	polyData_[0].su = 0;
	polyData_[0].sv = std::lerp(0.5f, 1, t);
	polyData_[1].su = 1;
	polyData_[1].sv = std::lerp(0.5f, 1, t);
	polyData_[2].su = 0;
	polyData_[2].sv = std::lerp(1, 0.5f, t);
	polyData_[3].su = 1;
	polyData_[3].sv = std::lerp(1, 0.5f, t);

}




void ResultDraw::SelectsDraw()
{
	for (auto& select : sharData_->selects)
	{
		auto prm = static_cast<int>(255 * select->blendParam);
		DxShDraw::DrawMULGraph(select->pos.x, select->pos.y,lpSkinImagePtr.GetImageHandle(select->image), prm, prm, prm);
	}
}

void ResultDraw::CreateResultImage(Beat::ResultDataConstPtr& result)
{
	auto& winSize = lpWindowSize->GetSize();

	auto inScreen = GetDrawScreen();
	SetDrawScreen(resultImage_);
	ClearDrawScreen();

	Vector2 pos;
	int x, y;
	auto image = lpSkinImagePtr.GetFirstImage(static_cast<Beat::SkinImageType>((*result->hitsData->result.begin()).first));

	GetGraphSize(image, &x, &y);
	pos.x = (winSize.x/2 - x)/2;
	pos.y = (winSize.y - y * static_cast<int>(result->hitsData->result.size()) ) /2;
	int numX, numY;
	//â∫ï~Ç´çÏê¨
	GetGraphSize(*numImage_.begin(), &numX, &numY);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	auto numString = std::to_string(Beat::maxScore);
	DrawBox(pos.x, pos.y,
		pos.x + x + numX * (static_cast<int>(numString.size()) + 2), pos.y + y * (static_cast<int>(result->hitsData->result.size()) + 1), 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//ï`âÊ
	auto draw = [&](Beat::SkinImageType&& type,const int& num) {
		image = lpSkinImagePtr.GetFirstImage(std::move(type));
		GetGraphSize(image, &x, &y);
		if (type == Beat::SkinImageType::JUST)
		{
			MakePoly(pos, x, y);
			DxShDraw::DrawGraph(polyData_, image, [&]() {
				SetUsePixelShader(shaderHandle_);
			SetUseTextureToShader(0, image);
			SetUseTextureToShader(1, subImage_); });
		}
		else
		{
			DrawGraph(pos.x, pos.y, image, true);
		}

		DrawNum(pos, x, y, num);
		pos.y += y;
	};

	draw(Beat::SkinImageType::Score, score_);
	for (auto& [type,num] : result->hitsData->result)
	{
		draw(static_cast<Beat::SkinImageType>(type), num);
	}

	SetDrawScreen(inScreen);

}

void ResultDraw::DrawNum(Vector2 pos, int sizeX,int sizeY, int num)
{
	auto numString = std::to_string(num);

	auto& winSize = lpWindowSize->GetSize();

	auto size = static_cast<int>(numString.size());

	int x, y;
	GetGraphSize(*numImage_.begin(), &x, &y);
	int cnt = 0;
	pos.x += x;
	for (auto numChar : numString)
	{
		DrawGraph(pos.x + sizeX + x * cnt++, (sizeY - y)/2 + pos.y, numImage_[std::atoi(&numChar)], true);
	}
	DrawGraph(pos.x + sizeX + x * cnt, (sizeY - y) / 2 + pos.y, lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::scoreX), true);
}

void ResultDraw::CreateNumImage()
{
	const auto& data = lpSkinImagePtr.GetAllImage(Beat::SkinImageType::num);
	for (int i =0; i < data.size(); i++)
	{
		numImage_[i] = data[i];
	}
}

