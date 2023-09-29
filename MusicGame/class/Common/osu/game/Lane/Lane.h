#pragma once
#include"../../../Base/GameObjBase.h"
#include<memory>
#include"../../LoadData.h"
#include"LaneDivision.h"
#include"LaneLength.h"

class SideSpaceDivision;
namespace Beat
{
	struct LoadData;
};

/// <summary>
/// ���[���Ɋւ��鏈�����܂Ƃ߂�N���X
/// </summary>
class Lane:
	public ObjBase
{
public:
	struct Initialization
	{
		LaneDivisionPtr division;
		LaneLengthPtr length;
	};
	Lane(Initialization& data);



private:
};

