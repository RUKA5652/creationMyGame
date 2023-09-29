#pragma once
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>
#include<vector>

class VKRenderPass
{
public:
	VkRenderPass renderPass;
	bool Init(const VkDevice& device,
		std::vector<std::pair<VkAttachmentDescription, VkAttachmentReference>> color,
		std::pair<VkAttachmentDescription, VkAttachmentReference> depth);

	void Begin(const VkCommandBuffer& cmdBuff, const VkFramebuffer& frameBuff, const VkExtent2D extent);

	void End(const VkCommandBuffer& cmdBuff);

};

