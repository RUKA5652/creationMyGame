#pragma once
#include "../../../Base/SetUp/SetUpGameObj.h"

class ReelSound;
/// <summary>
/// スピード設定シーン作成
/// </summary>
class SetUpSpeedAdjust :
	public SetUpGameObj
{
public:
	SetUpSpeedAdjust();
private:
	void MakeObj() override;

};
