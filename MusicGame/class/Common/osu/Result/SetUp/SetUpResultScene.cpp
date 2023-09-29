#include "SetUpResultScene.h"
#include"../Result.h"

SetUpResultScene::SetUpResultScene(const std::string& filePass, Beat::ResultDataConstPtr result, ResultScene::FuncData& funcData)
	:filePass_(filePass), result_(result), funcData_(std::move(funcData))
{

}

void SetUpResultScene::MakeObj()
{
	SetGameObj(std::make_unique<Result>(filePass_,result_, funcData_));
}
