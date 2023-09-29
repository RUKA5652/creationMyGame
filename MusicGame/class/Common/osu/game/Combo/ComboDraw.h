#pragma once
#include"../../../Base/Draw/DrawBase.h"
#include<memory>
#include<array>
#include"../../../template/Vector2.h"
#include "../DecisionData.h"


class ComboDraw
	:public DrawBase
{
public:
	ComboDraw(Beat::HitsDataConstPtr hitdata);
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
	void Draw() override;

private:
	void SetFunc(GameCore* gameCore) override;

	std::array<int, 10> numImage_;

	Vector2 imageSize_;

	Beat::HitsDataConstPtr hitdata_;

	int screen_;

	Vector2Flt screenSize_;
	
	int beforeCnt_;

	Timer::DeletaTime animStime_;

	float exSize_;

	void Init();


};

