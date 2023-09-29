#pragma once
#include"../../../Base/Draw/DrawBase.h"
#include "../DecisionTransform.h"
#include<map>
#include<filesystem>

class GameUIDraw:
	public DrawBase
{
public:
	GameUIDraw(LaneDivisionConstPtr division, DecisionTransformConstPtr data);
	~GameUIDraw();
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
	void Draw() override;

private:

	int screen_;

	std::map<std::string, int> keyHandle_;

	std::vector<int> playKeyHandle_;

	std::optional<float> changeDelta_;

	Timer::DeletaTime startPoint_;

	void SetFunc(GameCore* gameCore) override;

	void Init(LaneDivisionConstPtr& division, DecisionTransformConstPtr& data);

	void LoadKeyHandle(const std::filesystem::path& path, std::string&& name);

	void SetPlayKey(LaneDivisionConstPtr& division);

};

