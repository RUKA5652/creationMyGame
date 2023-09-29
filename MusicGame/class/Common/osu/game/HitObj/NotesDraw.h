#pragma once
#include<memory>
#include"../../../Base/Draw/DrawBase.h"
#include"NoteData.h"
#include "../DecisionData.h"
#include"../NoteSizeRatio.h"



class NotesDraw:
	public DrawBase
{
public:

	NotesDraw(LaneDivisionConstPtr division, Note::NotesDataConstPtr noteData, NoteSizeRatioConstPtr noteRatio, Beat::HitsDataConstPtr hitdata);
	~NotesDraw();


	void Draw();

private:
	Note::NotesDataConstPtr noteData_;
	NoteSizeRatioConstPtr noteRatio_;
	Beat::HitsDataConstPtr hitdata_;

	std::vector<int> normalImage_;
	std::vector<int> holdImage_;

	void CreateImage(LaneDivisionConstPtr& division);

	void SetFunc(GameCore* gameCore) override;

	void NormalDraw(Note::Normals normalsData) const;
	void HoldDraw(Note::Holds holdsData) const;




};

