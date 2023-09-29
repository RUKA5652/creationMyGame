#pragma once
#include <chrono>
#include"Timer.h"


/// <summary>
/// �o�ߎ��Ԍv�Z�N���X
/// </summary>
class LoopTimer
{
public:
	LoopTimer();
	virtual ~LoopTimer() {};
	//���Ԏ擾
	DeletaTimeConst& GetDeletaTime() const;
	//���Ԍv�Z
	virtual void UpdateDelta();
	//������
	void Reset();

protected:	
	//�N�_�̎���
	std::chrono::system_clock::time_point  startTime;
	//�I���̎���
	std::chrono::system_clock::time_point  endTime;
	//�o�ߎ���
	DeletaTime deltaTime_;
private:
	//�Z�b�g�A�b�v
	void SetUpDeletaTime();
};

using LoopTimerPtr = std::unique_ptr<LoopTimer>;
