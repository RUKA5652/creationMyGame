#pragma once
#include"../../../Base/Draw/DrawBase.h"
#include "../DecisionData.h"
#include"../../../template/Vector2.h"

class ScoreDraw:
	public DrawBase
{
public:
	ScoreDraw(Beat::HitsDataPtr hitdata);
	void Draw() override;
private:

	Beat::HitsDataPtr hitdata_;

	std::array<int, 10> numImage_;

	Vector2 imageSize_;

	int digits_;

	int maxCnt_;

	void SetFunc(GameCore* gameCore) override;
};

