#pragma once
#include"../Timer.h"

/// <summary>
/// 1���߂̃��Y��������
/// </summary>
class WaitSound
{
public:
	/// <param name="beatLength">���̌p������</param>
	/// <param name="waitSoundCount">���߂̔���</param>
	WaitSound(double beatLength,int waitSoundCount);
	~WaitSound();

	void WaitPlaySound(DeletaTimeConst& time);

private:
	//�ҋ@����
	DeletaTime waitTime_;
	//���̌p������
	double beatLength_;
	//���߂̔���
	int waitSoundCount_;
	//���Y���̉�
	int waitSoundHandle_;
	//�ǂݍ���
	void LoadFile();
#ifdef _SAVEJSON
	//��������
	void SaveFile();
#endif // _SAVEJSON


};

