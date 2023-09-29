#pragma once
#include<vulkan/vulkan_core.h>

class VKPipelineRasterization
{
public:
	VkPipelineRasterizationStateCreateInfo createInfo;
	void Init();
};

