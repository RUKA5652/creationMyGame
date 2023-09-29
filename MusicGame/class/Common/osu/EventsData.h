#pragma once
#include<string>
#include<memory>

namespace Beat
{
	/// <summary>
	/// osu�t�@�C���@�C�x���g���
	/// </summary>
	struct Events
	{
		//�w�i�C���[�W
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

