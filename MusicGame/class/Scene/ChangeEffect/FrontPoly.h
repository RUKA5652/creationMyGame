#pragma once
#include"EffectPoly.h"

class FrontPoly
	:public EffectPoly
{
public:
	FrontPoly(FLOAT4& size);
	~FrontPoly();
	void Update(Timer::DeletaTimeConst& time) override;

private:

	enum class State
	{
		MoveIpda,
		ScaleDown,
		MoveUp,
	};

	FLOAT4 scaleDownSize_;


	State state_;

	std::map<State,std::function<void(void)>> func_;

	int soundHandle_;

	void Init() override;

	void ScaleDown(FLOAT4& size ,float t);

	void MoveIpdaSize();

	void MoveScaleDown();

	void MoveUp();

};

