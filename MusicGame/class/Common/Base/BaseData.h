#pragma once
#include<memory>

class BaseData
{
public:
	virtual ~BaseData();

private:

};

using BaseDataPtr = std::shared_ptr<BaseData>;
using BaseDataConstPtr = std::shared_ptr<const BaseData>;
using BaseDataWeakPtr = std::weak_ptr<BaseData>;
