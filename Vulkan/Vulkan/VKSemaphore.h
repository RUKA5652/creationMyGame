#pragma once
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>

class VKSemaphore
{
public:
	VkSemaphore semphore;
	void Init(const VkDevice& device);
	void Destroy(const VkDevice& device);
};

