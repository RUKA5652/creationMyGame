#pragma once
#include"../../../Base/Update/UpdateBase.h"
#include "../../Select/Reel/ReelData.h"

class EqualizerEffect;
class ReelSound;
/// <summary>
/// タイトル文字の更新
/// </summary>
class TitleHedUpdate
	:public UpdateBase
{
public:
	TitleHedUpdate(Beat::ReelDataPtr reelData, EqualizerEffect* effect, ReelSound*& reelSound);

	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;

private:
	Beat::ReelDataPtr reelData_;
	EqualizerEffect* effect_;
	ReelSound* reelSound_;

	std::pair<std::string, int*> nowSound_;

};

