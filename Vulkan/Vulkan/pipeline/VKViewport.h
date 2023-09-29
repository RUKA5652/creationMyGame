#pragma once
#include<vulkan/vulkan_core.h>
#include<vulkan/vk_layer.h>

class VKViewport
{
public:
	VkViewport viewport;
	VkRect2D scissor;
	VkPipelineViewportStateCreateInfo creatInfo;
	void Init(const VkExtent2D& extent);
};

