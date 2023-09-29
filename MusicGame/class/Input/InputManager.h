#pragma once
#include<map>
#include<array>
#include<memory>
#include<vector>
#include"../Timer/Timer.h"

/// <summary>
/// インプット処理クラス
/// </summary>
class InputManager
{
public:
	using KeyCode = int;

	/// <summary>
	/// 入力情報
	/// </summary>
	struct InputData
	{
		KeyCode key;
		bool now;
		bool old;
		Timer::DeletaTime pushTime;
		InputData(KeyCode key);
		InputData();
		inline bool oneShot() const { return (now == true && old != now); } ;
	};
	//入力情報格納方式
	using InputResult = std::map<KeyCode, InputData>;

	InputManager(std::vector<std::pair<KeyCode,int>>&& init);
	~InputManager();
	//更新関数
	void Update(Timer::DeletaTimeConst& deletTime);
	//インプット結果取得
	const InputResult& GetInputData() const;
private:
	std::map<KeyCode, InputData> inputData_;
	std::array<char, 256> data;

};

using InputManagerPtr = std::unique_ptr<InputManager>;
