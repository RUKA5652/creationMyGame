#include "Score.h"
#include"ScoreDraw.h"

Score::Score(Beat::HitsDataPtr hitdata)
	:ObjBase(0, 1)
{
	draw_.emplace_back(std::make_shared<ScoreDraw>(hitdata));
}
