#pragma once
#include"../DecisionData.h"
#include <functional>


namespace Decision
{
	//�m�[�c���ʕ`��
	using SetDrawFunc = std::function<void(const Beat::Type& type)>;
	using SetDrawFuncPtr = std::shared_ptr<SetDrawFunc>;
}

