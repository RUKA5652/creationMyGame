#pragma once
#include"../../Base/BaseData.h"
#include<memory>
#include"../Difficulty.h"

/// <summary>
/// 画面両端の空きスペースのサイズ感を持つ
/// </summary>
class SideSpaceDivision
	:public BaseData
{
public:
	SideSpaceDivision();

	/// <summary>
	/// 取得
	/// 画面端をどれだけ残すのかの分割比
	/// </summary>
	const double& GetDivisionSpaceRatio() const;
	void SetDivison(double data);
private:


	//画面端をどれだけ残すのかの分割比
	double divisionSpaceRatio;

};
