#include "SetUpTitleScene.h"
#include"../TitleHed/TitleHed.h"
#include"../BackImage/TitleBackImage.h"
#include"../Cursor/TitleCursor.h"

SetUpTitleScene::SetUpTitleScene(ReelSound*& reelSound,Beat::ReelDataPtr reelData, std::shared_ptr<std::function<void(void)>> func)
	:reelSound_(reelSound)
{
	func_ = std::move(func);
	reelData_ = std::move(reelData);
}

void SetUpTitleScene::MakeObj()
{
	SetGameObj(std::make_unique<TitleHed>(reelData_, reelSound_));
	SetGameObj(std::make_unique<TitleBackImage>());
	SetGameObj(std::make_unique<TitleCursor>(func_));
}
