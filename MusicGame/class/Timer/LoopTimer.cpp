#include "LoopTimer.h"
#include <iostream>

LoopTimer::LoopTimer()
{
	SetUpDeletaTime();
}

void LoopTimer::SetUpDeletaTime()
{
	//�e�평����
	deltaTime_ = 0;
	Reset();
}

DeletaTimeConst& LoopTimer::GetDeletaTime() const
{
	return deltaTime_;
}


void LoopTimer::UpdateDelta()
{
	endTime = std::chrono::system_clock::now();
	//�N�_�̎��ԂƏI���̎��Ԃ̍������쐬
	deltaTime_ =static_cast<DeletaTime>((std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count()));

	startTime = endTime;
}

void LoopTimer::Reset()
{
	//�X�^�[�g�ƃG���h�𑵂��Ď��̌v���ɔ�����
	startTime = std::chrono::system_clock::now();
	endTime = startTime;
}

