#pragma once
#include<string>

/// <summary>
/// データ定義
/// OSUデータ MetaData
/// </summary>
namespace Beat
{
	//譜面メタルデータ
	struct MetaData
	{
		using TitleData = std::string;
		using CreatorData = std::string;
		//曲名
		TitleData Title;
		//曲の作者
		CreatorData Artist;
		//譜面作成バージョン
		std::string Version;
		//譜面作者
		CreatorData Creator;
		//構造体リセット
		void clear()
		{
			Title.clear();
			Artist.clear();
			Version.clear();
			Creator.clear();
		}
		auto operator<=>(const MetaData&) const = default;

	};
	using MetaDataPtr = MetaData*;

}

