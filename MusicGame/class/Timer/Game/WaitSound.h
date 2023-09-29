#pragma once
#include"../Timer.h"

/// <summary>
/// 1¬ß‚ÌƒŠƒYƒ€‚ğ‚Ş
/// </summary>
class WaitSound
{
public:
	/// <param name="beatLength">”‚ÌŒp‘±ŠÔ</param>
	/// <param name="waitSoundCount">¬ß‚Ì””</param>
	WaitSound(double beatLength,int waitSoundCount);
	~WaitSound();

	void WaitPlaySound(DeletaTimeConst& time);

private:
	//‘Ò‹@ŠÔ
	DeletaTime waitTime_;
	//”‚ÌŒp‘±ŠÔ
	double beatLength_;
	//¬ß‚Ì””
	int waitSoundCount_;
	//ƒŠƒYƒ€‚Ì‰¹
	int waitSoundHandle_;
	//“Ç‚İ‚İ
	void LoadFile();
#ifdef _SAVEJSON
	//‘‚«‚İ
	void SaveFile();
#endif // _SAVEJSON


};

