#pragma once
#include <string>
#include<filesystem>
#include<fstream>

namespace Beat
{
	/// <summary>
	/// �t�@�C���̃o�[�W���������擾����
	/// </summary>
	struct CheckVersion
	{
	private:
		const char* headData = "osu file format v";
	public:
		/// <summary>
		/// �t�@�C���̃o�[�W���������擾����
		/// </summary>
		/// <param name="filePass">�ǂݍ��݃t�@�C���̃p�X</param>
		/// <returns>���s-1�@�����@0�ȏ�̐��l</returns>
		int operator()(const std::string& filePass)
		{
			//-1�����s �O�ȏ�@version���

			//file�����݂��邩�m���߂�
			if (!std::filesystem::exists(filePass))
			{
				return -1;
			}
			//file���J��
			std::ifstream inFile(filePass);
			std::string buff;
			std::getline(inFile, buff);

			if (buff.starts_with(headData))
			{
				auto vnum = buff.rfind("v");
				buff.erase(0, ++vnum);
				return std::stoi(buff);
			}
			return -1;

		}
	};
}
