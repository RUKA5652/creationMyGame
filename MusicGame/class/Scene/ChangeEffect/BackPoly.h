#pragma once
#include"EffectPoly.h"

class BackPoly
	:public EffectPoly
{
public:
	BackPoly(FLOAT4& size);

	using EffectPoly::EffectPoly;
	void Update(Timer::DeletaTimeConst& time) override;
private:

	enum class State
	{
		MoveIpda,
		MoveScreen
	};

	FLOAT4 screenSize_;


	std::map<State, std::function<void(void)>> func_;

	State state_;

	void Init() override;

	void Scale(FLOAT4& size, float t);

	void MoveIpdaSize();

	void MoveScreen();
};

