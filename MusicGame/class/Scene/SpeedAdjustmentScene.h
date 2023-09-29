#pragma once
#include"BaseScene.h"

class SpeedAdjustmentScene
	:public BaseScene
{
public:
	SpeedAdjustmentScene(std::unique_ptr<BaseScene> before);
	~SpeedAdjustmentScene();
	void ProcessInput() override;
	std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> inScene) override;


	void DrawOnScreen() override;
private:

	std::unique_ptr<BaseScene> before_;

	void Init();

};

