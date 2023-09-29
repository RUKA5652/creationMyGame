#pragma once
#include "../../../Base/SetUp/SetUpGameObj.h"
#include"../../Select/Reel/ReelData.h"
#include<memory>
#include<functional>

class ReelSound;
/// <summary>
/// É^ÉCÉgÉãçÏê¨
/// </summary>
class SetUpTitleScene :
    public SetUpGameObj
{
public:
	SetUpTitleScene(ReelSound*& reelSound,Beat::ReelDataPtr reelData, std::shared_ptr<std::function<void(void)>> func_);
private:
	std::shared_ptr<std::function<void(void)>> func_;
	Beat::ReelDataPtr reelData_;
	ReelSound*& reelSound_;
	void MakeObj() override;

};

