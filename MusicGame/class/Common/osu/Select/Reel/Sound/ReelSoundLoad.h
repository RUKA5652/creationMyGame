#pragma once
#include<thread>
#include<string>
#include<map>
#include<queue>
#include<functional>
#include "../ReelData.h"



class ReelSound;

class ReelSoundLoad
{
public:
	ReelSoundLoad();
	~ReelSoundLoad();
	void LoadSound(ReelSound& reelSound);
	void LoadNowSound(ReelSound& reelSound);
	void Stop();

private:

	std::jthread thread_;

	std::queue<std::function<void(void)>> loadingList_;

	void LoadFunc(std::map<std::string, int>::iterator itr);

	void Thread(std::stop_token token);




};

