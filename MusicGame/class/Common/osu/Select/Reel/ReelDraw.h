#pragma once
#include"../../../Base/Draw/DrawBase.h"
#include"ReelData.h"
#include"Draw/FolderDraw.h"
#include"Draw/SelectScoreDraw.h"
#include "ReelAnimData.h"


class ReelDraw
	:public DrawBase
{
public:
	ReelDraw(Beat::ReelDataPtr reelData, ReelAnimData& animData);
	~ReelDraw();
	void Draw() override;

private:
	Beat::ReelDataPtr reelData_;

	int alphaBlend_;

	int blendScreen_;

	int buffHandle_;

	void SetFunc(GameCore* gameCore) override;

	std::shared_ptr<FolderDraw> folderDraw_;
	std::shared_ptr<SelectScoreDraw> scoreDraw_;
};

