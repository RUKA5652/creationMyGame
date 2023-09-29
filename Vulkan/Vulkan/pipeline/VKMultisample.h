#pragma once
#include<vulkan/vulkan_core.h>
class VKMultisample
{
public:
	VkPipelineMultisampleStateCreateInfo createInfo;
	void NoMultiSample();
};

