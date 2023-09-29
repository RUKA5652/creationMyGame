#pragma once
#include<vulkan/vulkan_core.h>

class VKSampler
{
public:
	VkSampler sampler;
	bool Init(const VkDevice& device);

};

