#include "ReelDraw.h"
#include<DxLib.h>
#include "../../../../Manager/ImageMng.h"
#include "../../../WindowSize.h"
#include"../../../Base/GameCore.h"
#include "../SelectDrawIndex.h"
#include"../../../../shaderDraw/DxShDraw.h"

ReelDraw::ReelDraw(Beat::ReelDataPtr reelData, ReelAnimData& animData)
{
	folderDraw_ = std::make_shared<FolderDraw>(reelData, animData);
	scoreDraw_ = std::make_shared<SelectScoreDraw>(reelData);
	reelData_ = std::move(reelData);
	alphaBlend_ = LoadPixelShader("resource/shader/MonoAddAlphaColor.pso");
	auto& size = lpWindowSize->GetSize();
	blendScreen_ = MakeScreen(size.x, size.y,true);
	buffHandle_ = CreateShaderConstantBuffer(sizeof(float) * 4);
}

ReelDraw::~ReelDraw()
{
	DeleteShader(alphaBlend_);
	DeleteGraph(blendScreen_);
	DeleteShaderConstantBuffer(buffHandle_);
}

void ReelDraw::Draw()
{
	if (!reelData_->sortData.size())
	{
		return;
	}
	auto& winSize = lpWindowSize->GetSize();
	auto data = reelData_->GetMapData();
	int handl = lpImageMng.GetID(data->path + data->image.filePass)[0];
	float grapX, grapY;
	GetGraphSizeF(handl, &grapX, &grapY);
	auto ratioX = winSize.x / static_cast<float>(grapX);
	auto ratioY = winSize.y / static_cast<float>(grapY);
	auto ratio =max(ratioX, ratioY);
	WindowSize::Size center = { winSize.x / 2, winSize.y / 2 };
	center.x += data->image.xOffset;
	center.y += data->image.yOffset;
	grapX *= ratio;
	grapY *= ratio;
	grapX /= 2;
	grapY /= 2;
	DrawExtendGraphF(center.x - grapX, center.y - grapY,
		center.x + grapX, center.y + grapY, handl, true);

	auto inScreem = GetDrawScreen();
	SetDrawScreen(blendScreen_);
	ClearDrawScreen();

	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	//DrawBox(0, 0, winSize.x, winSize.y, 0x000000, true);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(0, 0, inScreem, [&]() {
		SetUsePixelShader(alphaBlend_);
		SetUseTextureToShader(0, inScreem);
		auto buff = static_cast<float*>(GetBufferShaderConstantBuffer(buffHandle_));
		buff[0] = 0;
		buff[1] = 0;
		buff[2] = 0;
		buff[3] = 0.8f;
		UpdateShaderConstantBuffer(buffHandle_);
		SetShaderConstantBuffer(buffHandle_, DX_SHADERTYPE_PIXEL, 0);
		});

	SetDrawScreen(inScreem);
	ClearDrawScreen();
	DrawGraph(0, 0, blendScreen_,true);
}

void ReelDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(SelectDrawIndex::BackImage), shared_from_this());
	folderDraw_->SetFunc(gameCore);
	scoreDraw_->SetFunc(gameCore);
}
