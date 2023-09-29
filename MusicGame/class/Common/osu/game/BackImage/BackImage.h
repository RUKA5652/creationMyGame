#pragma once
#include"../../../Base/GameObjBase.h"
#include<memory>
#include"../../EventsData.h"

/// <summary>
/// ”wŒi•`‰æƒNƒ‰ƒX
/// </summary>
class BackImage:
	public ObjBase
{
public:
	BackImage(const std::string& musicScorePass,std::shared_ptr<const Beat::Events::BackImage> data);

private:
};

