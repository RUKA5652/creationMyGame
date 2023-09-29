#include "VKSampler.h"
#include <stdexcept>

bool VKSampler::Init(const VkDevice& device)
{
    VkSamplerCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
    //�t�B���^�[�ݒ�
    createInfo.minFilter = VK_FILTER_LINEAR;
    createInfo.magFilter = VK_FILTER_LINEAR;
    //UV�������Ƃ�
    createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
    //�ٕ����t�B���^�����O
    createInfo.maxAnisotropy = 1.0f;

    createInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_WHITE;

    if (vkCreateSampler(device, &createInfo, nullptr, &sampler) != VK_SUCCESS)
    {
        throw std::runtime_error("�T���v���[�쐬���s");
        return false;
    }

    return true;
}
