#pragma once
#include"DecisionDrawInterface.h"
#include<thread>

class DecisionDrawRePress:
	public DecisionDrawInterface
{
public:
	DecisionDrawRePress(Beat::HitsDataConstPtr hitsData);
	~DecisionDrawRePress();
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
	void Draw() override;

	void Create(const Beat::Type& type) override;


private:
	struct DrawData
		: public DecisionDrawInterface::DrawData
	{
		DrawData();
		bool flag;
		int sizeX;
		int sizeY;
		int subImage;
	};

	void InitPolyData();

	int shaderHandle_;

	int subImage_;

	int blur_;

	DrawData drawData_;

	std::array<VERTEX2DSHADER, 4> polyData_;

	std::jthread thred_;


};

