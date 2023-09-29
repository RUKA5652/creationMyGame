#pragma once
#include<vector>
#include<string>
#include<DxLib.h>

inline namespace GameKey
{
	struct KeyData
	{
		std::vector<std::pair<std::string, int>> key_;
		int center = 4;
		KeyData()
		{
			key_ =
			{
				{"A",KEY_INPUT_A},
				{"S",KEY_INPUT_S},
				{"D",KEY_INPUT_D},
				{"F",KEY_INPUT_F},
				{"SPACE",KEY_INPUT_SPACE},
				{"J",KEY_INPUT_J},
				{"K",KEY_INPUT_K},
				{"L",KEY_INPUT_L},
				{";",KEY_INPUT_SEMICOLON},
			};
		}

		auto operator()(int size)
		{
			std::vector<std::pair<std::string, int>> keyData(size);
			if (size % 2 == 0)
			{
				LoadEven(keyData);
			}
			else
			{
				LoadOdd(keyData);
			}

			return keyData;
		}

		void LoadOdd(std::vector<std::pair<std::string, int>>& keyData)
		{
			auto size = static_cast<int>(keyData.size());
			size = size / 2;
			int  cnt = 0;
			for (int i = size; i > 0; i--, cnt++)
			{
				keyData[cnt] = key_[center - i];
			}
			keyData[cnt++] = key_[center];
			for (int i = 1; i <= size; i++, cnt++)
			{
				keyData[cnt] = key_[center + i];
			}
		}
		void LoadEven(std::vector<std::pair<std::string, int>>& keyData)
		{
			auto size = static_cast<int>(keyData.size());
			size = size / 2;
			int  cnt = 0;
			for (int i = size; i > 0; i--, cnt++)
			{
				keyData[cnt] = key_[center - i];
			}
			for (int i = 1; i <= size; i++, cnt++)
			{
				keyData[cnt] = key_[center + i];
			}
		}
	};
}
