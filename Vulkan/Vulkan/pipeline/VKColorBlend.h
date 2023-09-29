#pragma once
#include<vulkan/vulkan_core.h>
#include<vulkan/vk_layer.h>

class VKColorBlend
{
public:
	VkPipelineColorBlendStateCreateInfo createInfo;
	VkPipelineColorBlendAttachmentState blendAttachment;

	void Init();

};

