#include "LoadEvent.h"
#include "../../../../../../_debug/_DebugConOut.h"
#include"LoadEventFunc.h"

namespace
{
	constexpr auto title("[Events]");
}


EventLoad::EventLoad()
	: LoadSectionBase(title)
{
	Init();
}

bool EventLoad::LoadFile(const std::string& fileData, Beat::LoadDataPtr data)
{
	return LoadSectionBase::LoadFile(fileData, data->eventsData);
}

void EventLoad::Init()
{
	setDataFuncVec_ =
	{
		std::bind_front(LoadEventFunc::Background())
	};
}


