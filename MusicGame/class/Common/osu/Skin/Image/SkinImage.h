#pragma once
#include<string>
#include<forward_list>
#include<map>
#include"SkinImageData.h"
#include "LoadSkinImage.h"
#include "../../HitObj.h"


#define lpSkinImagePtr SkinImage::GetInstance()

class SkinImage
{
public:
	static SkinImage& GetInstance()
	{
		static SkinImage skin_;
		return skin_;
	};
	
	int GetFirstImage(Beat::SkinImageType&& data);

	const std::vector<Beat::SkinImage>& GetAllImage(Beat::SkinImageType&& data);

	int GetAnimHandle(Beat::SkinImageType&& data);

	int GetImageHandle(int animHandle);

	void DeletAnimHandle(int animHandle);

	bool Update(int animHandle, const Beat::Time& time);

	void Update(const Beat::Time& time);

	void Reset(int animHandle);

	void SetStart(int animHandle);

private:
	SkinImage();
	~SkinImage();

	struct AnimData
	{
		AnimData() = default;
		AnimData(const std::vector<Beat::SkinImage>* image);
		int cnt;
	private:
		const std::vector<Beat::SkinImage>* image_;
		friend SkinImage;
	};

	int handleCnt_;

	std::map<int, AnimData> handleMap_;

	Beat::SkinImageMap skinMap_;

	LoadSkinImage loadSkin;

	void LoadDefault();

	bool Update(AnimData& data,const Beat::Time& time);


};

