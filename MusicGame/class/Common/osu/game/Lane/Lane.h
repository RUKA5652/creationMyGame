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
/// ƒŒ[ƒ“‚ÉŠÖ‚·‚éˆ—‚ğ‚Ü‚Æ‚ß‚éƒNƒ‰ƒX
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

