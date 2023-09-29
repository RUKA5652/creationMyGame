#include "VKQueueFamilyIndex.h"
#include<vector>
#include<vulkan/vulkan.hpp>
#ifdef _DEBUG
#include<iostream>
#endif //_DEBUG

bool VKQueueFamilyIndex::isComplete()
{
    bool flag = true;
    flag &= graphicsFamily.has_value();
    //flag &= presentFamily.has_value();

    return flag;
}

bool VKQueueFamilyIndex::Init(const VkPhysicalDevice& device)
{ 
    //キューファミリーのリスト作成
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
    std::vector<VkQueueFamilyProperties> queueFamilys(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilys.data());

#ifdef _DEBUG
    std::cout << "利用可のキュー出力:" << std::endl;
    for (const auto& queueFamily : queueFamilys)
    {
        std::cout << '\t' << "QueueFlags:";
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            std::cout << "VK_QUEUE_GRAPHICS_BIT,";
        }
        if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
        {
            std::cout << "VK_QUEUE_COMPUTE_BIT,";
        }
        if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
        {
            std::cout << "VK_QUEUE_TRANSFER_BIT,";
        }
        if (queueFamily.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT)
        {
            std::cout << "VK_QUEUE_SPARSE_BINDING_BIT,";
        }
        if (queueFamily.queueFlags & VK_QUEUE_PROTECTED_BIT)
        {
            std::cout << "VK_QUEUE_PROTECTED_BIT,";
        }
        if (queueFamily.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR)
        {
            std::cout << "VK_QUEUE_VIDEO_DECODE_BIT_KHR,";
        }
        std::cout << queueFamily.queueFlags << ":QueueCount:" << queueFamily.queueCount << std::endl;
    }

#endif // _DEBUG


    //グラフィックスキュー
    int i = 0;
    for (const auto& queueFamily : queueFamilys)
    {
        if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            graphicsFamily = i;
        }

        //プレゼンテーションキュー
        VkBool32 presentSupport = false;
  /*      vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);
        if (presentSupport)
        {
            presentFamily = i;
        }*/

        if (isComplete())
        {
            break;
        }
        i++;
    }
    return false;
}

std::set<uint32_t> VKQueueFamilyIndex::GetUniqueQueueFamilies() const
{
    return { graphicsFamily.value()/*,presentFamily.value()*/ };
}
