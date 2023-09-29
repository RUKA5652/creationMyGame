#include "VKFrameBuffer.h"
#include<array>

bool VKFrameBuffer::Init(const VkDevice& device,const VkRenderPass& renderPass,
	const VkExtent2D& extent, std::vector<VkImageView> image, VkImageView depth)
{
	VkFramebufferCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	createInfo.renderPass = renderPass;
	createInfo.width = extent.width;
	createInfo.height = extent.height;
	createInfo.layers = 1;

	frameBuffers.resize(image.size());
	for (int i = 0; i < image.size() ; i++)
	{
		std::array<VkImageView, 2> attachMents;
		attachMents[0] = image[i];
		attachMents[1] = depth;
		createInfo.attachmentCount = attachMents.size();
		createInfo.pAttachments = attachMents.data();
		vkCreateFramebuffer(device, &createInfo, nullptr, &frameBuffers[i]);
	}

	return false;
}
