#include "VKDevice.h"
#include<iostream>
#include<set>
#include"VKQueueFamilyIndex.h"


bool VKDevice::Init(const VKPhysicalDevice& physicalDevice, const VKInstance& instance)
{

    //�v������L���[�̐���ݒ肷��
    queueFamilyIndex.Init(physicalDevice.physicalDevice);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = queueFamilyIndex.GetUniqueQueueFamilies();
    //�D��x
    float queuePriority = 1.0f;
    //�L���[�ݒ�
    for (auto queueFamilyIndex : uniqueQueueFamilies)
    {
        VkDeviceQueueCreateInfo queueCreateInfo{};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamilyIndex;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        queueCreateInfos.emplace_back(queueCreateInfo);
    }

    //�f�o�C�X�@�\
    VkPhysicalDeviceFeatures deviceFeatures{};

    //�f�o�C�X�쐬Info
    VkDeviceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    //�L���[�̍쐬���Z�b�g
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    //�f�o�C�X�@�\���Z�b�g
    createInfo.pEnabledFeatures = &deviceFeatures;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(physicalDevice.deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = physicalDevice.deviceExtensions.data();
    //�Â������Ƃ̌݊����̂��ߐݒ�
#ifdef _DEBUG
    createInfo.enabledLayerCount = static_cast<uint32_t>(instance.validationLayers.size());
    createInfo.ppEnabledLayerNames = instance.validationLayers.data();
#else
    createInfo.enabledLayerCount = 0;
#endif // _DEBUG

    if (vkCreateDevice(physicalDevice.physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
    {
        throw std::runtime_error("�_���f�o�C�X�쐬���s");
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
    //�ҋ@����
    info.pWaitSemaphores = &presentSemaphore;
    info.signalSemaphoreCount = 1;
    //�`�悪�������Ă��邩�i�[
    info.pSignalSemaphores = &signalSemaphore;
    vkResetFences(device, 1, &commandFence);
    vkQueueSubmit(queue_.queue, 1, &info, commandFence);
}
