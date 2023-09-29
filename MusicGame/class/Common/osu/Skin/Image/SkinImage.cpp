#include "SkinImage.h"
#include"../DefaultPath.h"

int SkinImage::GetFirstImage(Beat::SkinImageType&& data)
{
    //return handleMap_.emplace(handleCnt_++, skinMap_.at(data).begin()).first->first;
    return *skinMap_.at(data).begin();
}

const std::vector<Beat::SkinImage>&  SkinImage::GetAllImage(Beat::SkinImageType&& data)
{
    return skinMap_.at(data);
}

int SkinImage::GetAnimHandle(Beat::SkinImageType&& data)
{
    auto animData = AnimData(&skinMap_[data]);
    return handleMap_.emplace(handleCnt_++,std::move(animData)).first->first;
}

int SkinImage::GetImageHandle(int handle)
{
    auto& data = handleMap_[handle];
    return (*data.image_)[data.cnt];
}

void SkinImage::DeletAnimHandle(int handle)
{
    handleMap_.erase(handle);
}

bool SkinImage::Update(int handle, const Beat::Time& time)
{
    return Update(handleMap_[handle], time);
}

void SkinImage::Update(const Beat::Time& time)
{
    for (auto& [key,data] : handleMap_)
    {
        Update(data, time);
    }
}

void SkinImage::Reset(int animHandle)
{
    handleMap_[animHandle].cnt = 0;
}

void SkinImage::SetStart(int handle)
{
    handleMap_[handle].cnt = 0;
}

bool SkinImage::Update(AnimData& data, const Beat::Time& time)
{
    int size = static_cast<int>(data.image_->size());
    if (++data.cnt >= size)
    {
        data.cnt = size - 1;
        return true;
    }
    return false;
}


SkinImage::SkinImage()
{
    LoadDefault();
    handleCnt_ = 0;
}

SkinImage::~SkinImage()
{
}

void SkinImage::LoadDefault()
{
    skinMap_ = loadSkin.LoadData(Skin::DefFilePath);
}

SkinImage::AnimData::AnimData(const std::vector<Beat::SkinImage>* image)
    :image_(image)
{
    cnt = 0;
}
