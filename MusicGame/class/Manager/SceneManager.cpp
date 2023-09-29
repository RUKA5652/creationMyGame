#include "SceneManager.h"
#include"../Scene/BaseScene.h"
#include<DxLib.h>
#include "../Scene/SelectScene.h"
#include "../../_debug/_DebugDispOut.h"

void SceneManager::ProcessInput()
{
	//nowScene_->ProcessInput();
	nowScene_->ProcessInput();

}

void SceneManager::Update()
{
	nowScene_ = nowScene_->Update(std::move(nowScene_));
	nowScene_->DrawOnScreen();
}

void SceneManager::Draw()
{
	nowScene_->Draw();
}

void SceneManager::run()
{
	while (DxLib::ProcessMessage() == 0)
	{
#ifdef _DEBUG
		_dbgStartDraw();
#endif // _DEBUG
		ProcessInput();
		Update();
		DxLib::SetDrawScreen(DX_SCREEN_BACK);
		DxLib::ClearDrawScreen();
		Draw();
#ifdef _DEBUG
		_dbgDraw();
		DxLib::DrawString(0, 27, ("deltaTime" + std::to_string(nowScene_->GetDeletaTime())).c_str(), 0xffffff);
		DxLib::DrawString(0, 27 + 27, ("FPS:" + std::to_string(DxLib::GetFPS())).c_str(), 0xffffff);
#endif // _DEBUG
		DxLib::ScreenFlip();
	}


}

void SceneManager::Delete()
{
	if (nowScene_)
	{
		nowScene_.reset();
	}
}


SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

