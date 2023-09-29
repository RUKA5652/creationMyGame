#include "ImageMng.h"
#include "../../_debug/_DebugConOut.h"
#include<DxLib.h>


const VecInt& ImageMng::GetID(const std::string& key)
{
	//if (imageMap_.find(key) == imageMap_.end())
	if (!imageMap_.count(key))
	{
		imageMap_[key].resize(1);
		imageMap_[key][0] = LoadGraph(key.c_str());
		handleUV_[imageMap_[key][0]] = {{0,0},{1,1}};
	}
 	
	return	imageMap_[key];

}

const VecInt& ImageMng::GetID(const std::string& f_name, const std::string& key)
{
	//if (imageMap_.find(key) == imageMap_.end())
	if (!imageMap_.count(key))
	{
		imageMap_[key].resize(1);
		imageMap_[key][0] = LoadGraph(f_name.c_str());
	}
	return	imageMap_[key];
}

const VecInt& ImageMng::GetID(const std::string& f_name, const std::string& key, const Vector2&& divSize, const Vector2&& divCnt)
{
	return GetID(f_name, key,divSize, divCnt);
}

const bool ImageMng::DeleteID(const std::string& key)
{
	if (imageMap_.count(key))
	{
		auto flag = false;
		for (auto image : imageMap_.at(key))
		{
			if (DeleteGraph(image))
			{
				handleUV_.erase(image);
				flag = true;
			}
		}
		return flag;
	}
	return false;
}

const std::pair<Vector2Flt, Vector2Flt> ImageMng::GetUV(int imagehndle)
{
	if (!handleUV_.count(imagehndle))
	{	
		//handleUV_.emplace(imagehndle, std::make_pair(Vector2Flt{ 0,0 }, Vector2Flt{ 1,1 }));
		return  std::make_pair(Vector2Flt{ 0,0 }, Vector2Flt{ 1,1 });
	}
	return handleUV_[imagehndle];
}

const int& ImageMng::LoadPSID(const std::string& f_name, const std::string& key)
{
	if (!shaderMap_.count(key))
	{
		shaderMap_[key] = LoadPixelShader(f_name.c_str());
		if (shaderMap_[key] == -1)
		{
			throw;
		}
	}
	return	shaderMap_[key];
}

const int ImageMng::GetPSID(const std::string& key)
{
	if (!shaderMap_.count(key))
	{
		return -1;
	}
	return	shaderMap_[key];
}

ImageMng::ImageMng()
{
}

ImageMng::BuffMng& ImageMng::GetBuffMng()
{
	return buffMng_;
}

const VecInt& ImageMng::GetID(const std::string& f_name, const std::string& key, const Vector2& divSize, const Vector2& divCnt)
{
	//if (imageMap_.find(key) == imageMap_.end())		//最後まで行くとendがくる
	if(!imageMap_.count(key))
	{
		TRACE("ファイル読み込み\n");
		imageMap_[key].resize(static_cast<UINT64>(divCnt.x) * static_cast<UINT64>(divCnt.y));

		LoadDivGraph(f_name.c_str()/*変換*/, divCnt.x * divCnt.y, divCnt.x, divCnt.y, divSize.x, divSize.y, &imageMap_[key][0], true);
		
		for (int i = 0; i < divCnt.x * divCnt.y; i++)
		{
			int x = i % divCnt.x;
			int y = (i / divCnt.x);

			Vector2Flt pos1 = { divSize.x * x ,divSize.y * y};
			Vector2Flt pos2 = { divSize.x * (x + 1) ,divSize.y * (y +1)};
			Vector2Flt size = divCnt.cast<float>() * divSize;
			Vector2Flt uv1 ;
			uv1.x = pos1.x == 0 ? 0 : pos1.x / size.x;
			uv1.y = pos1.y == 0 ? 0 : pos1.y / size.y;
			Vector2Flt uv2 = pos2 / size;
			handleUV_.emplace(imageMap_.at(key)[i],std::make_pair(uv1, uv2));
		}
	}
	return	imageMap_[key];
}



