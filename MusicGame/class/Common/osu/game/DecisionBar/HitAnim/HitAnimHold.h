#pragma once
#include"HitAnimBase.h"

class HitAnimHold
	:public HitAnimBase
{
public:
	HitAnimHold(LaneDivisionConstPtr division, DecisionTransformConstPtr transform);
	~HitAnimHold();
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
	void Draw() override;


private:
	struct Effect
	{
		int handle;
		Note::Pos pos;
		bool animFlag;
	};

	std::vector<Effect> handle_;

	std::vector<LaneBox> barBox_;

	Note::Size size_;

	void SetAnim(int index, bool flag) override;

	void SetFunc(GameCore* gameCore) override;

	void HandleSetUp();

	//int animHandle_;
};
