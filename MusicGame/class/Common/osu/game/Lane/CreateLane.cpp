#include "CreateLane.h"
#include"LaneDivision.h"
#include"LaneLength.h"
#include"../../../Base/SetUp/SetUpGameObj.h"

CreateLane::CreateLane(Beat::LoadDataCPtr& loadData,SideSpaceDivision*& sideData)
	:loadData_(loadData)
{
	sideData_ = sideData;
	initData_ = new  Lane::Initialization();
}

CreateLane::~CreateLane()
{
	delete initData_;
}

Lane::Initialization* CreateLane::CreateInitData()
{
	initData_->length = std::make_shared<LaneLength>();
	initData_->division = std::make_shared<LaneDivision>(loadData_->difficulty,sideData_, initData_->length);
	return initData_;
}

ObjBasePtr CreateLane::CreateObj()
{
	return std::make_unique<Lane>(*initData_);
}


