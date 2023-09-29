#define NOMINMAX
#include "ChangeEffect.h"
#include<DxLib.h>
#include"../../Common/WindowSize.h"
#include<cmath>
#include"FrontPoly.h"
#include"BackPoly.h"

ChangeEffect::ChangeEffect()
{
	auto& size = lpWindowSize->GetSize();
	ipadImage_ = LoadGraph("resource/skin/transition/ipad.png");
	moveTime_ = 0;
	ipadData_.x = 68;
	ipadData_.y = 12;
	ipadData_.z = 90;
	ipadData_.w = 11;

	front_ = new FrontPoly(ipadData_);
	back_ = new BackPoly(ipadData_);

	float x, y;
	GetGraphSizeF(ipadImage_, &x, &y);
	MakePoly(poly_, {-80,-20,0},{x,y,0});

	screenOutSize_ = { poly_[0].pos.x,poly_[0].pos.y,size.x - poly_[3].pos.x ,size.y - poly_[3].pos.y };

	
	MakePoly(front_->poly, { 0,0,0 }, { (float)size.x,(float)size.y,0 });
	MakePoly(back_->poly, { 0,0,0 }, { (float)size.x,(float)size.y,0 });

	myScreen_ = MakeScreen(size.x, size.y, true);


	state_ = State::MoveIpda;
	func_ = {
		{State::MoveIpda,std::bind(&ChangeEffect::MoveIpdaSize,this)},
		{State::MoveScreen,std::bind(&ChangeEffect::MoveScreen,this)},
	};

}

ChangeEffect::~ChangeEffect()
{
	DeleteGraph(ipadImage_);
	delete front_;
	delete back_;
}

void ChangeEffect::Update(Timer::DeletaTimeConst& time)
{
	moveTime_ += time;
	func_[state_]();
	front_->Update(time);
	back_->Update(time);
}

void ChangeEffect::Draw(BaseScene* scene, BaseScene* nextScene)
{
	auto inScreen = GetDrawScreen();
	if (nextScene != nullptr)
	{
		nextScene->DrawOnScreen();
	}
	SetDrawScreen(myScreen_);
	ClearDrawScreen();
	back_->Draw(nextScene);
	front_->Draw(scene);
	DrawPrimitive2D(poly_.data(),static_cast<int>(poly_.size()), DX_PRIMTYPE_TRIANGLESTRIP, ipadImage_, true);
	SetDrawScreen(inScreen);
	ClearDrawScreen();
	DrawGraph(0, 0, myScreen_, true);
}

bool ChangeEffect::GetEnd()
{
	return front_->GetEnd() && back_->GetEnd();
}


void ChangeEffect::Scale(FLOAT4& size, float t)
{
	auto& windSize = lpWindowSize->GetSize();
	poly_[0].pos.x = std::lerp(poly_[0].pos.x, size.x, t);
	poly_[0].pos.y = std::lerp(poly_[0].pos.y, size.y, t);

	poly_[1].pos.x = std::lerp(poly_[1].pos.x, windSize.x - size.z, t);
	poly_[1].pos.y = std::lerp(poly_[1].pos.y, size.y, t);

	poly_[2].pos.x = std::lerp(poly_[2].pos.x, size.x, t);
	poly_[2].pos.y = std::lerp(poly_[2].pos.y, windSize.y - size.w, t);

	poly_[3].pos.x = std::lerp(poly_[3].pos.x, windSize.x - size.z, t);
	poly_[3].pos.y = std::lerp(poly_[3].pos.y, windSize.y - size.w, t);
}


void ChangeEffect::MoveIpdaSize()
{
	auto t = std::min(moveTime_ / 1000.0f, 1.0f);
	auto pos = FLOAT4{ 0,0,0,0 };
	Scale(pos, t);
	if (moveTime_ >= 1250 + 750 + 300.0f)
	{
		state_ = State::MoveScreen;
		moveTime_ = 0;
	}
}

void ChangeEffect::MoveScreen()
{
	auto t = std::min(moveTime_ / 1000.0f, 1.0f);
	Scale(screenOutSize_, t);
}

void ChangeEffect::MakePoly(std::array<VERTEX2D, 4>& poly,VECTOR pos, VECTOR size)
{
	for (auto& v : poly) {
		v.rhw = 1.0f; 
		v.dif = GetColorU8(0xff, 0xff, 0xff, 0xff);
		v.u = 0.0f;
		v.v = 0.0f;
		v.pos.z = 0.0f;
	}

	poly[0].pos.x = pos.x;
	poly[0].pos.y = pos.y;
	poly[0].u = 0;
	poly[0].v = 0;


	poly[1].pos.x = poly[0].pos.x + size.x;
	poly[1].pos.y = poly[0].pos.y;
	poly[1].u = 1;
	poly[1].v = 0;

	poly[2].pos.x = poly[0].pos.x;
	poly[2].pos.y = poly[0].pos.y + size.y;
	poly[2].u = 0;
	poly[2].v = 1;

	poly[3].pos.x = poly[0].pos.x + size.x;
	poly[3].pos.y = poly[0].pos.y + size.y;
	poly[3].u = 1;
	poly[3].v = 1;
}



