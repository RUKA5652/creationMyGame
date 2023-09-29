#pragma once
#include"../../Base/Draw/DrawBase.h"
#include "ResultData.h"
#include"ResultSharingData.h"

class ResultDraw
	:public DrawBase
{
public:
	ResultDraw(const std::string& filePass, Beat::ResultDataConstPtr result, ResultSharingDataConstPtr sharData);
	~ResultDraw();

	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;

	void Draw() override;

private:

	void SetFunc(GameCore* gameCore) override;

	void DrawBackImage();

	void RankDraw();

	void MakePoly(Vector2 pos, int sizeX, int sizeY);

	void SelectsDraw();

	void CreateResultImage(Beat::ResultDataConstPtr& result);

	void DrawNum(Vector2 pos, int sizeX,int sizeY,int num);

	void CreateNumImage();

	ResultSharingDataConstPtr sharData_;

	Beat::ResultDataConstPtr result_;

	int backImage_;

	Vector2 pos_;

	int resultImage_;

	int score_;

	int shaderHandle_;

	int subImage_;

	Timer::DeletaTime time_;

	Timer::DeletaTime rankTime_;

	std::array<int, 10> numImage_;

	std::array<VERTEX2DSHADER, 4> polyData_;


};

