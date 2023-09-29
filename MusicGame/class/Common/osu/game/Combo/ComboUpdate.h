#pragma once
#include"../../../Base/Update/UpdateBase.h"
#include<memory>
#include<filesystem>
#include "../DecisionData.h"

class ComboUpdate
	:public UpdateBase
{
public:
	ComboUpdate(Beat::HitsDataConstPtr hitdata);
	~ComboUpdate();
	void Update(Timer::DeletaTimeConst& delta,const InputManager& input) override;

private:

	Beat::HitsDataConstPtr hitdata_;

	int oldHitCount_;

	std::vector<std::pair<int, int>> soundHandle_;

	std::vector<std::pair<int, int>>::iterator itr_;

	void CreateSound();
	void SetSound(const std::filesystem::path& path, std::string&& name);
};

