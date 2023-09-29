#pragma once
#include"../LoopTimer.h"
#include <string>
#include "../../Common/osu/LoadData.h"
#include<functional>

class WaitSound;

/// <summary>
/// ���ʂ̍Đ�����
/// </summary>
class GameClock
	:public LoopTimer
{
public:

	GameClock(const std::string& audioFile, Beat::LoadDataCPtr data, int& handle);
	~GameClock();
	void UpdateDelta() override;
private:
	int handle_;

	bool playFlag_;

	Beat::UpdateTime leadInTime_;
	//�X�V�֐��i�[
	std::function<void(void)> func_;

	double beatLength_;

	int meter_;

	WaitSound* waitSound_;

	void MusicUpdate();

	void WaitUpdate();

};

