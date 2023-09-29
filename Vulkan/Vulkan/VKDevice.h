#pragma once
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>
#include"VKPhysicalDevice.h"
#include"VKInstance.h"
#include "VKQueueFamilyIndex.h"
#include"VKQueue.h"


/// <summary>
/// �_���f�o�C�X
/// </summary>
class VKDevice
{
public:
	VkDevice device;
	//�L���[
	VKQueue queue_;
	//�L���[�t�@�~���[�C���f�b�N�X
	VKQueueFamilyIndex queueFamilyIndex;


	bool Init(const VKPhysicalDevice& physicalDevice, const VKInstance& instance);

	void QueueSubmit(const VkCommandBuffer& cmdBuffer, const VkSemaphore& presentSemaphore, const VkSemaphore& signalSemaphore, const VkFence& commandFence);

	
};

