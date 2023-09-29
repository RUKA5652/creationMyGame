#pragma once
#include <string>
#include<filesystem>
#include<fstream>

namespace Beat
{
	/// <summary>
	/// ファイルのバージョン情報を取得する
	/// </summary>
	struct CheckVersion
	{
	private:
		const char* headData = "osu file format v";
	public:
		/// <summary>
		/// ファイルのバージョン情報を取得する
		/// </summary>
		/// <param name="filePass">読み込みファイルのパス</param>
		/// <returns>失敗-1　成功　0以上の数値</returns>
		int operator()(const std::string& filePass)
		{
			//-1を失敗 ０以上　version情報

			//fileが存在するか確かめる
			if (!std::filesystem::exists(filePass))
			{
				return -1;
			}
			//fileを開く
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
