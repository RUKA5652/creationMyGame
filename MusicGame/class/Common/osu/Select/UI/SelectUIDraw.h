#pragma once
#include"../../../Base/Draw/DrawBase.h"
#include<DxLib.h>

class SelectUIDraw
	:public DrawBase
{
public:
	SelectUIDraw();
	~SelectUIDraw();

	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
	void Draw() override;

private:

	int guideHandle_;

	int maskHandle_;

	int shader_;

	int bufferHandle_;

	int time_;

	int screen_;


	FLOAT4 checkColor_;

	void SetFunc(GameCore* gameCore) override;



};

