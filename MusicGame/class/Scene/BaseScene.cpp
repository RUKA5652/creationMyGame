#include "BaseScene.h"
#include<DxLib.h>
#include"../Common/WindowSize.h"
#include"../SoundVolume/SoundVolume.h"

BaseScene::BaseScene()
{
	auto& size = lpWindowSize->GetSize();
	handle_ = MakeScreen(size.x, size.y,true);
}

BaseScene::~BaseScene()
{
	DeleteGraph(handle_);
}

void BaseScene::ProcessInput()
{
	timer_->UpdateDelta();
	input_->Update(timer_->GetDeletaTime());
	lpVolumeMng.ProcessInput();
}

void BaseScene::TimeUpdate()
{
	timer_->UpdateDelta();
}

void BaseScene::Draw()
{
	DrawGraph(0,0,handle_,true);
	lpVolumeMng.DrawParam({ 0, 0 });
}

void BaseScene::DrawUpdate()
{
	core_->DrawUpdate(timer_->GetDeletaTime(), *input_);
}

DeletaTimeConst& BaseScene::GetDeletaTime()
{
	return timer_->GetDeletaTime();
}

void BaseScene::DrawOnScreen()
{
	SetDrawScreen(handle_);
	ClearDrawScreen();
	core_->Draw();
}



