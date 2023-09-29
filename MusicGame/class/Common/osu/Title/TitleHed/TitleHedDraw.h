#pragma once
#include"../../../Base/Draw/DrawBase.h"
#include "../../Select/Reel/ReelData.h"
#include"../../../../SoundWaveEffect/EqualizerEffect.h"

/// <summary>
/// ƒ^ƒCƒgƒ‹•¶Žš•`‰æ
/// </summary>
class TitleHedDraw
	:public DrawBase
{
public:
	TitleHedDraw(EqualizerEffect* effect);
	void Draw() override;
private:
	void SetFunc(GameCore* gameCore) override;

	EqualizerEffect* effect_;

	std::pair<EqualizerEffect::SetUpParam, EqualizerEffect::Pos>  Load();

};

