#include"NoteData.h"


Note::NormalData::NormalData(const Beat::Time& geneTime, const Beat::Time& endTime)
	:generatTime(geneTime),endTime(endTime)
{
}

Note::HoldData::HoldData(const Beat::Time& geneTime)
	: generatTime(geneTime)
{
	holdTime = geneTime;
}
