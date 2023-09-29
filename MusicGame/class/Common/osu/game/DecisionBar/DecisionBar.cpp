#include "DecisionBar.h"
#include"DecisionBarDraw.h"
#include"DecisionDraw.h"
#include"LightDraw.h"
#include"HitAnim/DecisionHitAnim.h"
#include"../DecisionTransform.h"
#include"../../../Base/GameCore.h"


DecisionBar::DecisionBar(Beat::HitsDataPtr hitsData, DecisionTransformConstPtr transform, 
	LaneDivisionConstPtr division, NoteSizeRatioConstPtr noteSize,
	Note::NotesDataConstPtr notesData,Beat::LoadDataCPtr loadData)
	:ObjBase(1, 3)
{
	auto setAnim = std::make_shared<Decision::AnimSetFunc>();
	auto setDraw = std::make_shared<Decision::SetDrawFunc>();
	update_.emplace_back(std::make_unique<DecisionUpdate>(hitsData, transform, notesData, loadData, setAnim, setDraw));
	draw_ = {
		{std::make_shared<DecisionDraw>(hitsData,setDraw)},
		{std::make_shared<DecisionBarDraw>(division, transform)},
		{std::make_shared<LightDraw>(division, transform)},
		{std::make_shared<DecisionHitAnim>(division,transform,setAnim)},
	};
}

