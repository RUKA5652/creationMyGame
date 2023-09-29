#pragma once
#include"../../Base/GameObjBase.h"
#include"ResultData.h"
#include"../../../Scene/ResultScene.h"

class Result
	:public ObjBase
{
public:
	Result(const std::string& filePass,Beat::ResultDataConstPtr result, ResultScene::FuncData& func);
	~Result();

private:



};

