#include "ObliqueLaneDraw.h"
#include"../../../../Base/GameCore.h"
#include"../LaneDivision.h"
#include"../../../../WindowSize.h"
#include<DxLib.h>
#include "../../GameDrawIndex.h"

ObliqueLaneDraw::ObliqueLaneDraw(LaneDivisionConstPtr&& divData)
	:draw_(divData)
{
	handle_ = -1;
	effectHandle_ = -1;
	MakeScreen();
	MakePolyGon();
	state_ = State::Set;
}

ObliqueLaneDraw::~ObliqueLaneDraw()
{
	DeleteGraph(handle_);
	DeleteGraph(effectHandle_);
}

void ObliqueLaneDraw::Draw()
{
	switch (state_)
	{
	case State::Set:
		SetScreen();
		state_ = State::LaneDraw;
		return;
	case State::LaneDraw:
		draw_.Draw();
		state_ = State::DrawSetScreen;
		return;
	case State::DrawSetScreen:
		DrawOblique();
		state_ = State::SetEffect;
		return;
	case State::SetEffect:
		SetEffectScreen();
		state_ = State::DrawEffect;
		return;
	case State::DrawEffect:
		DrawEffectScreen();
		state_ = State::Set;
		return;
	default:
		break;
	}


}

void ObliqueLaneDraw::DrawLane()
{
	draw_.Draw();
}

void ObliqueLaneDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::SetObliqueScreen), shared_from_this());
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::DrawObliqueScreen), shared_from_this());
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::Lane), shared_from_this());
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::SetAddEffectScreen), shared_from_this());
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::DrawAddEffectScreen), shared_from_this());
}


void ObliqueLaneDraw::SetScreen()
{
	inHandle_ = GetDrawScreen();
	SetDrawScreen(handle_);
	ClearDrawScreen();
}

void ObliqueLaneDraw::DrawOblique()
{
	SetDrawScreen(inHandle_);
	DrawPrimitive3D(polyData_.data(),static_cast<int>(polyData_.size()), DX_PRIMTYPE_TRIANGLESTRIP, handle_, true);
	//DrawGraph(0, 0, handle_,true);
}

void ObliqueLaneDraw::SetEffectScreen()
{
	inHandle_ = GetDrawScreen();
	SetDrawScreen(effectHandle_);
	ClearDrawScreen();
}

void ObliqueLaneDraw::DrawEffectScreen()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
	SetDrawScreen(inHandle_);
	DrawPrimitive3D(polyData_.data(), static_cast<int>(polyData_.size()), DX_PRIMTYPE_TRIANGLESTRIP, effectHandle_, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}


void ObliqueLaneDraw::MakeScreen()
{
	DeleteGraph(handle_);
	DeleteGraph(effectHandle_);
	auto& windowSize = lpWindowSize->GetSize();
	handle_ = DxLib::MakeScreen(windowSize.x, windowSize.y, true);
	effectHandle_ = DxLib::MakeScreen(windowSize.x, windowSize.y, true);
}

void ObliqueLaneDraw::MakePolyGon()
{
	auto& windowSize = lpWindowSize->GetSize();
	for (auto& d : polyData_)
	{
		d.dif = GetColorU8(255, 255, 255, 255);
		d.spc = GetColorU8(0, 0, 0, 0);
	}

	polyData_[0].pos.x = 0;
	polyData_[0].pos.y = -250;
	polyData_[0].pos.z = 0;
	polyData_[0].u = 0;
	polyData_[0].v = 1;
	polyData_[1].pos.x = static_cast<float>(windowSize.x);
	polyData_[1].pos.y = -250;
	polyData_[1].pos.z = 0;
	polyData_[1].u = 1;
	polyData_[1].v = 1;

	polyData_[2].pos.x = 0;
	polyData_[2].pos.y = static_cast<float>(windowSize.y + 500);
	polyData_[2].pos.z = 700;
	polyData_[2].u = 0;
	polyData_[2].v = 0;
	polyData_[3].pos.x = static_cast<float>(windowSize.x);
	polyData_[3].pos.y = static_cast<float>(windowSize.y + 500);
	polyData_[3].pos.z = 700;
	polyData_[3].u = 1;
	polyData_[3].v = 0;



}





