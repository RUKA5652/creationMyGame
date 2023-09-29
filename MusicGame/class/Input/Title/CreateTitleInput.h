#pragma once
#include"../BaseCreateInput.h"
#include"TitleSceneInput.h"

class CreateTitleInput:
	public BaseCreateInput
{
public:
	void operator()(InputManagerPtr& ptr) override;



private:



};

