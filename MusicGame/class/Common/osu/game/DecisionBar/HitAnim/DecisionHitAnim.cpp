#include "DecisionHitAnim.h"
#include "../../GameDrawIndex.h"
#include"../../../../Base/GameCore.h"
#include"HitAnimNormal.h"
#include"HitAnimHold.h"

using namespace Decision;

DecisionHitAnim::DecisionHitAnim(LaneDivisionConstPtr division, DecisionTransformConstPtr transform,
	std::shared_ptr<Decision::AnimSetFunc> setAnim)
{
	anim_[static_cast<size_t>(AnimType::Normal)] = std::make_unique<HitAnimNormal>(division,transform);
	anim_[static_cast<size_t>(AnimType::Holde)] = std::make_unique<HitAnimHold>(division, transform);
	*setAnim = std::bind_front(&DecisionHitAnim::SetAnim,this);
}

DecisionHitAnim::~DecisionHitAnim()
{
	
}

void DecisionHitAnim::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	for (auto& anim : anim_)
	{
		anim->Update(delta, input);
	}
}

void DecisionHitAnim::Draw()
{
	for (auto& anim : anim_)
	{
		anim->Draw();
	}
}

void DecisionHitAnim::SetAnim(int index, bool flag, Decision::AnimType animType)
{
	anim_[static_cast<size_t>(animType)]->SetAnim(index,flag);
}

void DecisionHitAnim::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::NotesLight), shared_from_this());
}
