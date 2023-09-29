#pragma once
#include<vulkan/vulkan_core.h>
#include<vulkan/vk_layer.h>
#include<vector>

class VKFrameBuffer
{
public:
	std::vector<VkFramebuffer> frameBuffers;
	bool Init(const VkDevice& device, const VkRenderPass& renderPass,const VkExtent2D& extent,std::vector<VkImageView> image,VkImageView depth);


};

