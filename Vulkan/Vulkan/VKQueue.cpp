#include "VKQueue.h"

bool VKQueue::Init(const VkDevice& device,const uint32_t& queueFamilyIndex, uint32_t queueIndex)
{
    vkGetDeviceQueue(device,queueFamilyIndex,queueIndex,&queue);
    return true;
}
