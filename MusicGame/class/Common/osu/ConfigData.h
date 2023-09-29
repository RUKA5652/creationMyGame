#pragma once

namespace Beat
{
	/// <summary>
	/// コンフィグデータ
	/// デフォルトファイル・ユーザーファイルがなかった時ようにデータを入れておく
	/// </summary>
	struct ConfigData
	{
		using mSpeed = int;
		using sidDivison = float;
		mSpeed ManiaSpeed = 15;
		sidDivison SideSpaceDivison = 0.25f;
	};
	
	using ConfigDataPtr = ConfigData*;
}

