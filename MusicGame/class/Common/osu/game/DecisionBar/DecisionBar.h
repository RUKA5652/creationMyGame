#pragma once
#include"../../../Base/GameObjBase.h"
#include<memory>
#include"../../../Base/Draw/DrawBase.h"
#include"../NoteSizeRatio.h"
#include"DecisionUpdate.h"
#include"../DecisionData.h"
#include"../DecisionTransform.h"
#include"../Lane/LaneDivision.h"

class LaneLength;
/// <summary>
/// îªíËÉoÅ[
/// </summary>
class DecisionBar:
	public ObjBase
{
public:
	DecisionBar(Beat::HitsDataPtr hitsData, DecisionTransformConstPtr transform, LaneDivisionConstPtr division,
		NoteSizeRatioConstPtr noteSize, Note::NotesDataConstPtr notesData, Beat::LoadDataCPtr loadData);

private:


};

