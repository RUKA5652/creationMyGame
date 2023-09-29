#pragma once
#include"../../../../Base/Draw/DrawBase.h"
#include"../../DecisionData.h"
#include"../../DecisionTransform.h"
#include"HitAnimEnum.h"


class HitAnimBase
	:public DrawBase
{
public:
	virtual void SetAnim(int index,bool flag) = 0;
private:

};

