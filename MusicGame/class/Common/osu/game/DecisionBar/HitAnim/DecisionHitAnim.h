#pragma once
#include"../../../../Base/Draw/DrawBase.h"
#include"../../DecisionData.h"
#include"../../DecisionTransform.h"
#include"HitAnimEnum.h"
#include"HitAnimBase.h"

class DecisionHitAnim
	:public DrawBase
{
public:
	DecisionHitAnim(LaneDivisionConstPtr division, DecisionTransformConstPtr transform,
		std::shared_ptr<Decision::AnimSetFunc> setAnim);
	~DecisionHitAnim();
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
	void Draw() override;


private:

	void SetAnim(int index,bool flag, Decision::AnimType animType);

	void SetFunc(GameCore* gameCore) override;

	std::array<std::unique_ptr<HitAnimBase>, static_cast<size_t>(Decision::AnimType::MAX)> anim_;
};

