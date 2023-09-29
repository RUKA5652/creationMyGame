#pragma once
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>
#include"VKPhysicalDevice.h"
#include"VKInstance.h"
#include "VKQueueFamilyIndex.h"
#include"VKQueue.h"


/// <summary>
/// 論理デバイス
/// </summary>
class VKDevice
{
public:
	VkDevice device;
	//キュー
	VKQueue queue_;
	//キューファミリーインデックス
	VKQueueFamilyIndex queueFamilyIndex;


	bool Init(const VKPhysicalDevice& physicalDevice, const VKInstance& instance);

	void QueueSubmit(const VkCommandBuffer& cmdBuffer, const VkSemaphore& presentSemaphore, const VkSemaphore& signalSemaphore, const VkFence& commandFence);

	
};

