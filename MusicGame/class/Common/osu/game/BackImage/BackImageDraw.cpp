#include "BackImageDraw.h"
#include <filesystem>
#include<DxLib.h>
#include "../../../WindowSize.h"
#include"../../../Base/GameCore.h"
#include"../GameDrawIndex.h"

BackImageDraw::BackImageDraw(const std::string& musicScorePass, std::shared_ptr<const Beat::Events::BackImage> data)
{
	std::filesystem::path pass = musicScorePass;
	pass.replace_filename(data->filePass);
	handle_ = LoadGraph(pass.string().c_str());
	pos = {data->xOffset, data->yOffset};
}

BackImageDraw::~BackImageDraw()
{
	DeleteGraph(handle_);
}

void BackImageDraw::Draw()
{

	auto& winSize = lpWindowSize->GetSize();
	int grapX, grapY;
	GetGraphSize(handle_, &grapX, &grapY);
	auto ratioX = winSize.x / static_cast<float>(grapX);
	auto ratioY = winSize.y / static_cast<float>(grapY);
	auto ratio = static_cast<int>(max(ratioX, ratioY));
	WindowSize::Size center = { winSize.x / 2, winSize.y / 2 };
	center.x += pos.x;
	center.y += pos.y;
	grapX *= ratio;
	grapY *= ratio;
	grapX /= 2;
	grapY /= 2;
	DrawExtendGraph(center.x - grapX, center.y - grapY,
		center.x + grapX, center.y + grapY, handle_, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(0, 0, winSize.x, winSize.y, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void BackImageDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::BackImage), shared_from_this());
}
