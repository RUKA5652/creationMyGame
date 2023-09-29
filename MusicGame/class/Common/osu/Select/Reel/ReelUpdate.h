#pragma once
#include"../../../Base/Update/UpdateBase.h"
#include"ReelData.h"
#include"Data/SortReelData.h"
#include"Sound/ReelSound.h"
#include"../../../../Scene/UsingChangeSceneFunc.h"
#include"ReelAnimData.h"

class ReelUpdate
	:public UpdateBase
{
public:
	ReelUpdate(Beat::ReelDataPtr reelData, ReelSound* reelSound, ReelAnimData& animData,const ChengeSceneFunc::CreateGameFunc& func);

	~ReelUpdate();

	void Update(Timer::DeletaTimeConst& delta,const InputManager& input) override;

private:
	enum class Sound
	{
		BeatMap,
		Group,
		Decision
	};

	enum class MoveDir
	{
		UP,
		DOWN,
	};

	SortReelData sortFunc_;
	ReelSound* sound_;

	ChengeSceneFunc::CreateGameFunc chengeGameColl_;

	Beat::ReelDataPtr reelData_;

	std::map<Sound, int> soundEffect_;

	ReelAnimData& animData_;

	Timer::DeletaTime time_;

	void Init();

	void MoveBeatMap(MoveDir dir);
	void MoveMainGroup(MoveDir dir);

	void MoveMainGroup(int cnt);

};

