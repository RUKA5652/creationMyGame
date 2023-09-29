#pragma once
#include"image/VKImage.h"
#include <vulkan/vk_layer.h>
#include"VKSwapchain.h"


class VKDepth:
	public VKImage
{
public:
	bool Init(const VkDevice& device, const VmaAllocator& allocator, const VKSwapchain& swapChain);
	std::pair<VkAttachmentDescription, VkAttachmentReference> GetAttachment();
};

