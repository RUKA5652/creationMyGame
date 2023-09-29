#include "VKSampler.h"
#include <stdexcept>

bool VKSampler::Init(const VkDevice& device)
{
    VkSamplerCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    //フィルター設定
    createInfo.minFilter = VK_FILTER_LINEAR;
    createInfo.magFilter = VK_FILTER_LINEAR;
    //UV超えたとき
    createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    //異方性フィルタリング
    createInfo.maxAnisotropy = 1.0f;

    createInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;

    if (vkCreateSampler(device, &createInfo, nullptr, &sampler) != VK_SUCCESS)
    {
        throw std::runtime_error("サンプラー作成失敗");
        return false;
    }

    return true;
}
