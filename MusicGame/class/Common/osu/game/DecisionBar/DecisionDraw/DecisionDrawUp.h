#pragma once
#include"DecisionDrawInterface.h"

class DecisionDrawUp:
	public DecisionDrawInterface
{
public:
	DecisionDrawUp(Beat::HitsDataConstPtr hitsData);

	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
	void Draw() override;

	void Create(const Beat::Type& type) override;

private:
	std::deque<DrawData> dataDeque_;


};

