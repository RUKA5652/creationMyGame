#pragma once
#include"../../../Base/SetUp/SetUpGameObj.h"
#include"../ResultData.h"
#include"../../../../Scene/ResultScene.h"

class SetUpResultScene
	: public SetUpGameObj
{
public:
	SetUpResultScene(const std::string& filePass,Beat::ResultDataConstPtr result,ResultScene::FuncData& funcData);
private:

	void MakeObj() override;
	ResultScene::FuncData funcData_;
	Beat::ResultDataConstPtr result_;
	const std::string filePass_;

};

