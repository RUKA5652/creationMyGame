#pragma once
#include"HitAnimBase.h"

class HitAnimNormal
	:public HitAnimBase
{
public:
	HitAnimNormal(LaneDivisionConstPtr division, DecisionTransformConstPtr transform);
	~HitAnimNormal();
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
	void Draw() override;


private:
	struct Effect
	{
		int handle;
		Note::Pos pos;
	};

	std::deque<Effect> handle_;
	std::deque<Effect> poolHandle_;

	std::vector<LaneBox> barBox_;

	Note::Size size_;

	void SetAnim(int index,bool flag) override;

	void SetFunc(GameCore* gameCore) override;


	//int animHandle_;
};
