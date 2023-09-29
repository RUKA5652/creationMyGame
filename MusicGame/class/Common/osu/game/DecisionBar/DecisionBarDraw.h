#pragma once
#include"../../../Base/Draw/DrawBase.h"
#include<memory>
#include<functional>
#include"../DecisionTransform.h"
#include"../Lane/LaneDivision.h"
#include "../DecisionData.h"


/// <summary>
/// ����o�[�`��N���X
/// </summary>
class DecisionBarDraw:
	public DrawBase
{
public:
	DecisionBarDraw(LaneDivisionConstPtr division, DecisionTransformConstPtr data);
	~DecisionBarDraw();

	void Draw() override;

private:

	int image_;

	int screenHndle;

	std::shared_ptr<const Beat::HitsData> hitsData_;

	void SetFunc(GameCore* gameCore) override;

	void CreateDrawData(LaneDivisionConstPtr& division,
		DecisionTransformConstPtr& data);



};

