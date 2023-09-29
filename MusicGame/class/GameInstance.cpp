#include "GameInstance.h"
#include<Dxlib.h>
#include <chrono>
#include"Manager/SceneManager.h"
#include"Common/WindowSize.h"
#include"Common/osu/Skin/Image/SkinImage.h"
#include"Common/osu/Skin/Sound/SkinSound.h"
#include"RandSeed/RandSeed.h"

#include"Scene/SelectScene.h"
#include"Scene/TitleScene.h"
#include "../_debug/_DebugConOut.h"
#include"../_debug/_DebugDispOut.h"

#include"../resource.h"

bool GameInstance::operator()(SceneManager& sceneManager)
{
#ifdef _DEBUG
	DxLib::SetOutApplicationLogValidFlag(true);
#else
	DxLib::SetOutApplicationLogValidFlag(false);
#endif // _DEBUG
	auto& windowSize = lpWindowSize->GetSize();
	DxLib::ChangeWindowMode(true);
	DxLib::SetMainWindowText("FallBeat");
	DxLib::SetGraphMode(windowSize.x, windowSize.y, 32);
	//SetNotDrawFlag(true);
	SetUseLighting(false);
	SetAlwaysRunFlag(true);
	//垂直同期
	//DxLib::SetWaitVSyncFlag(false);
	//サウンドAPI切り替え
	DxLib::SetEnableWASAPIFlag(true, false, 0);
	//ドラッグ＆ドロップ
	DxLib::SetDragFileValidFlag(true);
	//再生時間取得type
	SetSoundCurrentTimeType(DX_SOUNDCURRENTTIME_TYPE_SOFT);
	SetCreateSoundIgnoreLoopAreaInfo(true);

	SetWindowIconID(IDI_ICON1);
	if (DxLib::DxLib_Init() != 0)
	{
		return false;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	//DxLib::SetBackgroundColor(0x00, 0x00, 0x00);


	_dbgSetup(windowSize.x, windowSize.y, 32);

	lpSkinImagePtr;
	lpSkinSoundPtr;
	lpSeedMng;
	//sceneManager.nowScene_ = std::make_unique<SelectScene>();
	sceneManager.nowScene_ = std::make_unique<TitleScene>();

	return true;
}
