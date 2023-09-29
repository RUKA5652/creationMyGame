#include "Result.h"
#include"ResultDraw.h"
#include"ResultUpdate.h"
#include"ResultSharingData.h"


Result::Result(const std::string& filePass, Beat::ResultDataConstPtr result, ResultScene::FuncData& func)
	: ObjBase(1, 1)
{
	auto sharData = std::make_shared<ResultSharingData>(filePass,result,func);
	draw_.emplace_back(std::make_shared<ResultDraw>(filePass,result, sharData));
	update_.emplace_back(std::make_unique<ResultUpdate>(sharData));

}


Result::~Result()
{
}
