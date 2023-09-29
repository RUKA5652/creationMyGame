#include "BackImage.h"
#include<DxLib.h>
#include <filesystem>
#include"../../../WindowSize.h"
#include"BackImageDraw.h"
#include"../../../Base/GameCore.h"

BackImage::BackImage(const std::string& musicScorePass, std::shared_ptr<const Beat::Events::BackImage> data)
	:ObjBase(0,1)
{
	draw_.emplace_back(std::make_shared<BackImageDraw>(musicScorePass, data));

}


