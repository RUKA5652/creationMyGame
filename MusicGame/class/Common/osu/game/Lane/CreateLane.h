#pragma once
#include"../../../Base/SetUp/CreateSupport.h"
#include "../../LoadData.h"
#include"Lane.h"

class LaneDivision;
class LaneLength;
class SideSpaceDivision;


class CreateLane
	:public CreateSupport<Lane::Initialization,Lane>
{
public:
	CreateLane(Beat::LoadDataCPtr& loadData, SideSpaceDivision*& sideData );
	~CreateLane();


	Lane::Initialization* CreateInitData() override;
	ObjBasePtr CreateObj() override;

private:
	Beat::LoadDataCPtr& loadData_;
	const SideSpaceDivision* sideData_;



};

