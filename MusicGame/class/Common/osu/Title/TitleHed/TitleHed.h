#pragma once
#include"../../../Base/GameObjBase.h"
#include "../../Select/Reel/ReelData.h"

class EqualizerEffect;
class ReelSound;
/// <summary>
/// �^�C�g������
/// </summary>
class TitleHed
	:public ObjBase
{
public:
	TitleHed(Beat::ReelDataPtr reelData, ReelSound*& reelSound);
	~TitleHed();
private:
	Beat::ReelDataPtr reelData_;
	EqualizerEffect* effect_;
};

