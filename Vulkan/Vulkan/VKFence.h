#pragma once
#include<vulkan/vulkan_core.h>
#include<vulkan/vk_layer.h>
#include<vector>

class VKFence
{
public:
	std::vector<VkFence> fence;
	bool Init(const VkDevice& device, uint32_t count);
};

