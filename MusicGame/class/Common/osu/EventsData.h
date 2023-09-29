#pragma once
#include<string>
#include<memory>

namespace Beat
{
	/// <summary>
	/// osuファイル　イベント情報
	/// </summary>
	struct Events
	{
		//背景イメージ
		struct BackImage
		{
			std::string filePass;
			int xOffset = 0;
			int yOffset = 0;
		};

		std::shared_ptr<BackImage> image_;

		void clear()
		{
			image_ = std::make_shared<BackImage>();
		}
	};

	using EventsPtr = Events*;
}

