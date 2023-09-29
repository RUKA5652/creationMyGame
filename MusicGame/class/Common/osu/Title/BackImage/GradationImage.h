#pragma once
#include <DxLib.h>
/// <summary>
/// グラデーション作成
/// </summary>
class GradationImage
{
public:
	using Color = FLOAT3;
	using Pos = FLOAT2;
	Color startColor;
	Color endColor;
	Pos startPos;
	Pos endPos;
	GradationImage();
	~GradationImage();
	void operator()(int handle);
private:
	int shader_;
};

