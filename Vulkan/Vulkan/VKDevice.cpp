#include "VKDevice.h"
#include<iostream>
#include<set>
#include"VKQueueFamilyIndex.h"


bool VKDevice::Init(const VKPhysicalDevice& physicalDevice, const VKInstance& instance)
{

    //要求するキューの数を設定する
    queueFamilyIndex.Init(physicalDevice.physicalDevice);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = queueFamilyIndex.GetUniqueQueueFamilies();
    //優先度
    float queuePriority = 1.0f;
    //キュー設定
    for (auto queueFamilyIndex : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.emplace_back(queueCreateInfo);
    }

    //デバイス機能
    VkPhysicalDeviceFeatures deviceFeatures{};

    //デバイス作成Info
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    //キューの作成情報セット
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    //デバイス機能情報セット
    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(physicalDevice.deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = physicalDevice.deviceExtensions.data();
    //古い実装との互換性のため設定
#ifdef _DEBUG
    createInfo.enabledLayerCount = static_cast<uint32_t>(instance.validationLayers.size());
    createInfo.ppEnabledLayerNames = instance.validationLayers.data();
#else
    createInfo.enabledLayerCount = 0;
#endif // _DEBUG

    if (vkCreateDevice(physicalDevice.physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
    {
        throw std::runtime_error("論理デバイス作成失敗");
        return false;
    }
    return queue_.Init(device,queueFamilyIndex.graphicsFamily.value(),0 );
}

void VKDevice::QueueSubmit(const VkCommandBuffer& cmdBuffer,const VkSemaphore& presentSemaphore, const VkSemaphore& signalSemaphore,const VkFence& commandFence)
{
    VkPipelineStageFlags waitStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

    VkSubmitInfo info{};
    info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    info.commandBufferCount = 1;
    info.pCommandBuffers = &cmdBuffer;
    info.pWaitDstStageMask = &waitStageMask;
    info.waitSemaphoreCount = 1;
    //待機条件
    info.pWaitSemaphores = &presentSemaphore;
    info.signalSemaphoreCount = 1;
    //描画が完了しているか格納
    info.pSignalSemaphores = &signalSemaphore;
    vkResetFences(device, 1, &commandFence);
    vkQueueSubmit(queue_.queue, 1, &info, commandFence);
}
