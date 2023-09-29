#include "FolderDraw.h"
#include "../../../../../Manager/ImageMng.h"
#include "../../../../WindowSize.h"
#include "../../../Skin/Image/SkinImage.h"
#include"../../../../Base/GameCore.h"
#include"../../../../../shaderDraw/DxShDraw.h"
#include "../../SelectDrawIndex.h"
#include"HSVtoRGB.h"
#include"RGBtoHSV.h"

namespace
{
	namespace NoColor
	{
		static int r = 0xff;
		static int g = 0x6f;
		static int b = 0x5f;
	}

	namespace Color
	{
		constexpr int r = 0x41;
		constexpr int g = 0xdf;
		constexpr int b = 0xff;
	}

	namespace LevelColor
	{
		constexpr int sR = 0x00;
		constexpr int sG = 0xff;
		constexpr int sB = 0x00;
		constexpr int eR = 0xff;
		constexpr int eG = 0x00;
		constexpr int eB = 0xff;
	}

	namespace ThumbnailSize
	{
		constexpr auto x = 115;
		constexpr auto y = 85;
		constexpr auto offset = 9;
	};
	namespace NoSelect
	{
		constexpr auto CenterX = 1210;
	}
	namespace Select
	{
		constexpr auto Offset = -100;
	}
	namespace StringOffset
	{
		constexpr int x = 9;
	}

	namespace Level
	{
		constexpr const char* level = "Level:";
	}

}





FolderDraw::FolderDraw(Beat::ReelDataPtr reelData, ReelAnimData& animData)
	:animData_(animData)
{
	reelData_ = std::move(reelData);
	Init();
}

FolderDraw::~FolderDraw()
{
	DeleteGraph(drawHandle_);
}

void FolderDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	if (animData_.state == ReelAnimData::State::SeletEndAnim)
	{
		time_ += delta;
		if (flashFlag_)
		{
			flashFlag_ = time_ < 150;
			if (!flashFlag_)
			{
				time_ = 0;
			}
		}
		else
		{
			flashFlag_ = time_ > 150;
			if (flashFlag_)
			{
				time_ = 0;
			}
		}
	}

}


void FolderDraw::Draw()
{
	auto inDrawMode = GetDrawMode();
	if (!reelData_->sortData.size())
	{
		return;
	}
	int inScreen = GetDrawScreen();
	SetDrawScreen(drawHandle_);
	ClearDrawScreen();
	DrawSelectGroup();
	SetDrawScreen(inScreen);
	DrawNotSelectGroup();
	DrawGraph(0, 0, drawHandle_, true);
	SetDrawMode(inDrawMode);
}


void FolderDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(SelectDrawIndex::Folder), shared_from_this());
}

void FolderDraw::Init()
{
	GetGraphSize(lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::MusicFolder), &folderImageSize_.x, &folderImageSize_.y);
	auto& winSize = lpWindowSize->GetSize();
	centerPosY_ = (winSize.y - folderImageSize_.y) / 2;
	upIndexCnt_ = 0;
	downIndexCnt_ = 0;
	time_ = 0;
	flashFlag_ = true;
	drawHandle_ = MakeScreen(winSize.x, winSize.y, true);

}


void FolderDraw::DrawSelectGroup()
{
	auto mapGroupData = reelData_->GetMapGroupData();
	downIndexCnt_ = 1;
	int index = reelData_->mapGroupIndex_.value();
	while (++index != static_cast<int>(mapGroupData->size()))
	{
		DrawMenu(Select::Offset / 2, centerPosY_ + ThumbnailSize::y * downIndexCnt_, (*mapGroupData)[index], true);
		downIndexCnt_++;
	}

	index = reelData_->mapGroupIndex_.value();
	upIndexCnt_ = 1;
	while (--index != -1)
	{
		DrawMenu(Select::Offset / 2, centerPosY_ - ThumbnailSize::y * upIndexCnt_, (*mapGroupData)[index], true);
		upIndexCnt_++;
	}

	if (flashFlag_)
	{
		DrawBox(NoSelect::CenterX - folderImageSize_.x / 2 + Select::Offset, centerPosY_,
			folderImageSize_.x + NoSelect::CenterX - folderImageSize_.x / 2 + Select::Offset, folderImageSize_.y + centerPosY_, 0xffff00, true);
	}

	DrawMenu(Select::Offset, centerPosY_, reelData_->GetMapData(), true);



}

void FolderDraw::DrawNotSelectGroup()
{
	auto& windSize = lpWindowSize->GetSize();
	int index = reelData_->mainSortIndex_.value();
	int posY = centerPosY_ + ThumbnailSize::y * downIndexCnt_;
	while (posY < windSize.y)
	{
		index = ++index == reelData_->sortData.size() ? 0:index;

		DrawMenu(0, posY, reelData_->sortData[index], false);
		downIndexCnt_++;
		posY = centerPosY_ + ThumbnailSize::y * downIndexCnt_;
	}
	index = reelData_->mainSortIndex_.value();
	posY = centerPosY_ - ThumbnailSize::y * upIndexCnt_;
	while (posY > -folderImageSize_.y)
	{
		index = --index >= 0  ? index : static_cast<int>(reelData_->sortData.size())-1;

		DrawMenu(0, posY, reelData_->sortData[index], false);
		upIndexCnt_++;
		posY = centerPosY_ - ThumbnailSize::y * upIndexCnt_;
	}


}



void FolderDraw::DrawMenu(int offsetX, int offsetY, Beat::ReelData::MapGroup& group, bool flag)
{
	DrawMenu(offsetX, offsetY, *group.begin(), flag);
}

void FolderDraw::DrawMenu(int offsetX, int offsetY,const Beat::BeatMap* map, bool flag)
{
	int handl = lpImageMng.GetID(map->path + map->image.filePass)[0];
	int folderHandl = lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::MusicFolder);
	int levelHandl = lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::Level);

	auto posX = NoSelect::CenterX - folderImageSize_.x / 2 + offsetX;
	//背景描画
	if (flag)
	{
		DrawMULGraph(posX,  offsetY, folderHandl, Color::r, Color::g, Color::b);
	}
	else
	{
		DrawMULGraph(posX,  offsetY, folderHandl, NoColor::r, NoColor::g, NoColor::b);
	}
	int folderSizeX, folderSizeY;
	GetGraphSize(folderHandl, &folderSizeX, &folderSizeY);


	//サムネ描画
	SetDrawMode(DX_DRAWMODE_ANISOTROPIC);
	posX += ThumbnailSize::offset;
	auto posY = (folderImageSize_.y - ThumbnailSize::y) / 2  + offsetY;
	DrawModiGraph(posX, posY,
		posX + ThumbnailSize::x, posY,
		posX + ThumbnailSize::x, posY + ThumbnailSize::y,
		posX, posY + ThumbnailSize::y, handl, true);
	posX += StringOffset::x;
	//タイトル描画
	SetDrawMode(DX_DRAWMODE_NEAREST);
	DrawExtendString(posX + ThumbnailSize::x, posY, 2, 2, map->metaDatas.Title.c_str(), 0xffffff, 0x000000);
	if (!flag)
	{
		return;
	}
	//難易度名描画
	int fSizeX, fSizeY, fCnt;
	GetDrawExtendFormatStringSize(&fSizeX, &fSizeY, &fCnt, 2, 2, map->metaDatas.Title.c_str());
	posY += fSizeY;
	DrawExtendString(posX + ThumbnailSize::x, posY, 1.5, 1.5, map->metaDatas.Version.c_str(), 0xffffff, 0x000000);
	GetDrawExtendFormatStringSize(&fSizeX, &fSizeY, &fCnt, 1.5, 1.5, map->metaDatas.Version.c_str());
	//難易度レベル描画
	posY = posY +  ((offsetY + folderSizeY /*bottom*/) - posY) / 2;
	DrawExtendString(posX + ThumbnailSize::x, posY, 1, 1, Level::level, 0xffffff, 0x000000);
	GetDrawExtendFormatStringSize(&fSizeX, &fSizeY, &fCnt, 1, 1, Level::level);
	//数の重み
	float tWeight = 1.0f/15.0f;
	//カラーデータ
	constexpr FLOAT3 SColor{LevelColor::sR,LevelColor::sG ,LevelColor::sB };
	constexpr FLOAT3 EColor{ LevelColor::eR,LevelColor::eG ,LevelColor::eB };
	FLOAT3 hsvSColor = RGBtoHSV()(SColor);
	FLOAT3 hsvEColor = RGBtoHSV()(EColor);
	FLOAT3 hsvColor = hsvSColor;
	//求める
	auto getColor = [&](float t) {
		FLOAT3 hsv;
		hsv.x = std::lerp(hsvSColor.x, hsvEColor.x, t);
		hsv.y = std::lerp(hsvSColor.y, hsvEColor.y, t);
		hsv.z = std::lerp(hsvSColor.z, hsvEColor.z, t);
		return HSVtoRGB()(hsv);
	};

	for (float cnt = 0, t = tWeight; cnt < map->Level; cnt++,t += tWeight)
	{
		auto x = static_cast<int>(posX + ThumbnailSize::x + fSizeX + cnt * 20 );
		auto color = getColor(t);
		SetDrawBright(static_cast<int>(color.x), static_cast<int>(color.y), static_cast<int>(color.z));
		DrawExtendGraph(x, posY,x + 15 , posY + 15, levelHandl,true);
	}
	SetDrawBright(255, 255, 255);
	

}
