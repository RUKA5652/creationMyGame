#pragma once
#include"../BaseCreateInput.h"
#include"SelectSceneInput.h"

class CreateSelectInput:
	public BaseCreateInput
{
public:
	void operator()(InputManagerPtr& ptr) override;



private:



};

