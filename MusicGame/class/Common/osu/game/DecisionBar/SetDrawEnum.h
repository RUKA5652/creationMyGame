#pragma once
#include"../DecisionData.h"
#include <functional>


namespace Decision
{
	//ƒm[ƒcŒ‹‰Ê•`‰æ
	using SetDrawFunc = std::function<void(const Beat::Type& type)>;
	using SetDrawFuncPtr = std::shared_ptr<SetDrawFunc>;
}

