#include "VKFence.h"
#include <stdexcept>


bool VKFence::Init(const VkDevice& device, uint32_t count)
{
    VkFenceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    createInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;
    fence.resize(count);
    fence.shrink_to_fit();
    for (auto& f : fence)
    {
        if (vkCreateFence(device, &createInfo, nullptr, &f) != VkResult::VK_SUCCESS)
        {
            throw std::runtime_error("ÉtÉFÉìÉXçÏê¨é∏îs");
            return false;
        }
    }
    return true;
}
