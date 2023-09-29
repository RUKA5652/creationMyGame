#pragma once
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>

class VKQueue
{
public:
	VkQueue queue;
	bool Init(const VkDevice& device, const uint32_t& queueFamilyIndex, uint32_t queueIndex);
};

