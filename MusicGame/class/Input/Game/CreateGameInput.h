#pragma once
#include"../BaseCreateInput.h"
#include"GameSceneInputKey.h"

class CreateGameInput:
	public BaseCreateInput
{
public:
	void operator()(InputManagerPtr& ptr) override;
	void operator()(InputManagerPtr& ptr,int size);


private:

};

