#pragma once
#include<DxLib.h>
#include "../BaseScene.h"

class EffectPoly
{
public:
	EffectPoly(FLOAT4& ipadData);

	virtual void Update(Timer::DeletaTimeConst& time) = 0;

	virtual void Draw(BaseScene* scene) final;

	std::array<VERTEX2D, 4> poly;

	bool GetEnd();

protected:
	FLOAT4& ipadData_;
	Timer::DeletaTime moveTime_;

	bool endFlag_;

	virtual void Init();

};

