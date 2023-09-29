#include "VulkanAppBase.h"
#include<vector>
#include <iostream>
#include<algorithm>
#include"vma/vma_imp.h"

VulkanAppBase& VulkanAppBase::GetInstance()
{
    static VulkanAppBase* appBasePtr_ = nullptr;
    if (!appBasePtr_)
    {
        appBasePtr_ = new VulkanAppBase();
    }

    return *appBasePtr_;
}


VulkanAppBase::VulkanAppBase()
{
}

bool VulkanAppBase::MakeVmaAllocator(const VkInstance& instance, const VkPhysicalDevice& physicalDevice, const VkDevice& device)
{
    VmaAllocatorCreateInfo allocatorInfo = {};
    allocatorInfo.instance = instance;
    allocatorInfo.physicalDevice = physicalDevice;
    allocatorInfo.device = device;
    allocatorInfo.flags = VMA_ALLOCATOR_CREATE_KHR_DEDICATED_ALLOCATION_BIT;
    allocatorInfo.vulkanApiVersion = VK_API_VERSION_1_1;
    if(vmaCreateAllocator(&allocatorInfo, &allocator_) != VkResult::VK_SUCCESS)
    {
        //例外
        throw std::runtime_error("アロケータ 失敗");
        return false;
    }

    return true;
}

void VulkanAppBase::Init(GLFWwindow* window, const char* appName)
{
    instance_.Init(appName);
    physicalDevice_.Init(instance_.instance);
    device_.Init(physicalDevice_,instance_);
    MakeVmaAllocator(instance_.instance, physicalDevice_.physicalDevice, device_.device);

    commandPool_.Init(device_.device, device_.queueFamilyIndex);
    surface_.Init(instance_.instance,physicalDevice_.physicalDevice,VkFormat::VK_FORMAT_B8G8R8A8_UNORM, window);
    swapchain_.Init(device_.device,surface_, device_.queueFamilyIndex, window);
    depthBuff_.Init(device_.device, allocator_ ,swapchain_);
    renderPass_.Init(device_.device, { swapchain_.GetAttachment() }, depthBuff_.GetAttachment());
    frameBuffer_.Init(device_.device, renderPass_.renderPass, swapchain_.extent, swapchain_.imageView, depthBuff_.imageView);
    commandBuffer_.Init(device_.device, commandPool_.commandPool, swapchain_.imageView.size());
    commandFence.Init(device_.device, swapchain_.imageView.size());
    renderCompleted_.Init(device_.device);
    presentCompleted_.Init(device_.device);
}

void VulkanAppBase::Release()
{
    depthBuff_.Release(allocator_);

}

void VulkanAppBase::Prepare()
{
}

void VulkanAppBase::Render()
{
    uint32_t nextImageIndex = 0;
    vkAcquireNextImageKHR(device_.device, swapchain_.swapChain, UINT64_MAX, presentCompleted_.semphore, nullptr, &nextImageIndex);
    vkWaitForFences(device_.device, 1, &commandFence.fence[nextImageIndex], VK_TRUE, UINT64_MAX);
    commandBuffer_.Begin(nextImageIndex);
    const auto& cmdBuff = commandBuffer_.commandBuffer[nextImageIndex];
    renderPass_.Begin(cmdBuff,frameBuffer_.frameBuffers[nextImageIndex],swapchain_.extent);
    imageIndex_ = nextImageIndex;
    
    if (makeCommand_)
    {
        makeCommand_(cmdBuff, imageIndex_);
    }

    renderPass_.End(cmdBuff);
    commandBuffer_.End(nextImageIndex);

    device_.QueueSubmit(cmdBuff,presentCompleted_.semphore,renderCompleted_.semphore,commandFence.fence[nextImageIndex]);

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = &swapchain_.swapChain;
    presentInfo.pImageIndices = &nextImageIndex;
    presentInfo.waitSemaphoreCount = 1;
    //待機条件
    presentInfo.pWaitSemaphores = &renderCompleted_.semphore;
    vkQueuePresentKHR(device_.queue_.queue, &presentInfo);

}

void VulkanAppBase::SetDrawCmd(DrawCmd func)
{
    makeCommand_ = func;
}

void VulkanAppBase::MakeGraphicsPipeline(const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages, const VkPipelineVertexInputStateCreateInfo* shaderInfo)
{
    pipeline_.GraphicsInit(device_.device, renderPass_.renderPass, pipeline_.pipeline, pipeline_.layout, swapchain_.extent, shaderStages, shaderInfo);
}

void VulkanAppBase::MakePipelineLayout(const VkPipelineLayoutCreateInfo& createInfo)
{
    vkCreatePipelineLayout(device_.device, &createInfo, nullptr,&pipeline_.layout);
}

void VulkanAppBase::MakePipeline(const VkGraphicsPipelineCreateInfo& createInfo)
{
    if (vkCreateGraphicsPipelines(device_.device, VK_NULL_HANDLE, 1, &createInfo, nullptr, &pipeline_.pipeline) != VK_SUCCESS)
    {
        std::cerr << "MakePipeline失敗" << std::endl;
    }
}

const VkDevice& VulkanAppBase::GetVkDevice()
{
    return device_.device;
}

const VKPhysicalDevice& VulkanAppBase::GetVKPhysicalDevice()
{
    return physicalDevice_;
}

const VKSwapchain& VulkanAppBase::GetVKSwapchain()
{
    return swapchain_;
}

const VkRenderPass& VulkanAppBase::GetVkRenderPass()
{
    return renderPass_.renderPass;
}

const VKPipeline& VulkanAppBase::GetVKPipeline()
{
    return pipeline_;
}

const VmaAllocator& VulkanAppBase::GetAllocator()
{
    return allocator_;
}

const VkCommandPool& VulkanAppBase::GetCommandPool()
{
    return commandPool_.commandPool;
}

const VkQueue& VulkanAppBase::GetVkQueue()
{
    return device_.queue_.queue;
}
