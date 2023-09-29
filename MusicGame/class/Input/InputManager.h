#pragma once
#include<map>
#include<array>
#include<memory>
#include<vector>
#include"../Timer/Timer.h"

/// <summary>
/// �C���v�b�g�����N���X
/// </summary>
class InputManager
{
public:
	using KeyCode = int;

	/// <summary>
	/// ���͏��
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
	//���͏��i�[����
	using InputResult = std::map<KeyCode, InputData>;

	InputManager(std::vector<std::pair<KeyCode,int>>&& init);
	~InputManager();
	//�X�V�֐�
	void Update(Timer::DeletaTimeConst& deletTime);
	//�C���v�b�g���ʎ擾
	const InputResult& GetInputData() const;
private:
	std::map<KeyCode, InputData> inputData_;
	std::array<char, 256> data;

};

using InputManagerPtr = std::unique_ptr<InputManager>;
