#pragma once
#include"../../Base/BaseData.h"
#include<memory>
#include "HitObj/NoteData.h"
#include"Lane/LaneDivision.h"

/// <summary>
/// ノーツをどれだけのサイズ感で出すのかの値を持つ
/// </summary>
class NoteSizeRatio
	:public BaseData
{
public:
	NoteSizeRatio(LaneDivisionConstPtr&& division);

	const double& GetHeightRatio() const;

	const Note::Size& GetSize() const;

private:

	void LoadRatio(LaneDivisionConstPtr& division);

	double ratio_;

	Note::Size size_;

};

using NoteSizeRatioPtr = std::shared_ptr<NoteSizeRatio>;
using NoteSizeRatioConstPtr = std::shared_ptr<const NoteSizeRatio>;