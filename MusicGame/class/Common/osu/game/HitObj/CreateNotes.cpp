#include"CreateNotes.h"
#include"../Lane/LaneDivision.h"
#include"../NoteSizeRatio.h"
#include"../DecisionTransform.h"
#include"../../../Base/SetUp/SetUpGameObj.h"

CreateNotes::CreateNotes(HitObjVecConstPtr objData, LaneDivisionPtr division, LaneLengthPtr length)
{
	initData_ = new Notes::Initialization
	{
		nullptr,
		nullptr,
		nullptr,
		division,
		length,
		nullptr
	};
	objData_ = objData;
}

CreateNotes::~CreateNotes()
{
	delete initData_;
}

Notes::Initialization* CreateNotes::CreateInitData()
{
	if (!initData_->hitdata)
	{
		initData_->hitdata = std::make_shared<Beat::HitsData>(initData_->division->divisionData);
	}
	if (!initData_->noteData)
	{
		initData_->noteData = std::make_shared<Note::NotesData>(initData_->division->divisionData);;
	}
	if (!initData_->noteSize)
	{
		initData_->noteSize = std::make_shared<NoteSizeRatio>(initData_->division);
	}
	if (!initData_->decisionData)
	{
		initData_->decisionData = std::make_shared<DecisionTransform>(initData_->noteSize, initData_->length);
	}


	return initData_;
}

ObjBasePtr CreateNotes::CreateObj()
{
	return nullptr;
}

ObjBasePtr CreateNotes::CreateObj(std::function<void(void)> func)
{
	return std::make_unique<Notes>(objData_, *initData_, func);
}