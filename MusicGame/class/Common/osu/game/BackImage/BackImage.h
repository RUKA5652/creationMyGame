#pragma once
#include"../../../Base/GameObjBase.h"
#include<memory>
#include"../../EventsData.h"

/// <summary>
/// �w�i�`��N���X
/// </summary>
class BackImage:
	public ObjBase
{
public:
	BackImage(const std::string& musicScorePass,std::shared_ptr<const Beat::Events::BackImage> data);

private:
};

