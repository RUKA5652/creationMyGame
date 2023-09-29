#include "TitleBackImage.h"
#include<DxLib.h>
#include"TitleBackImageDraw.h"

TitleBackImage::TitleBackImage()
	:ObjBase(0,1)
{
	draw_.emplace_back(std::make_shared<TitleBackImageDraw>());

}


