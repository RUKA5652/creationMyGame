#pragma once
#include "../BaseScene.h"
#include<DxLib.h>

class EffectPoly;

class ChangeEffect
{
public:
	ChangeEffect();
	~ChangeEffect();

	void Update(Timer::DeletaTimeConst& time);

	void Draw(BaseScene* scene, BaseScene* nextScene);

	bool GetEnd();

private:

	std::array<VERTEX2D,4> poly_;
	EffectPoly* front_;
	EffectPoly* back_;

	int myScreen_;

	int ipadImage_;

	FLOAT4 ipadData_;

	FLOAT4 screenOutSize_;

	Timer::DeletaTime moveTime_;

	enum class State
	{
		MoveIpda,
		MoveScreen
	};

	std::map<State, std::function<void(void)>> func_;

	State state_;

	void MakePoly(std::array<VERTEX2D, 4>& poly,VECTOR pos,VECTOR size);

	void Scale(FLOAT4& size, float t);

	void MoveIpdaSize();

	void MoveScreen();

};

