#pragma once
#include <vulkan/vk_layer.h>
#include<vector>
#include"VKSurface.h"
#include"VKQueueFamilyIndex.h"


class VKSwapchain
{
public:
	VkSwapchainKHR swapChain;
	VkExtent2D extent;
	std::vector<VkImageView> imageView;
	VkFormat format;
	bool Init(const VkDevice& device,const VKSurface& surface,const VKQueueFamilyIndex& queueFamilyIndex, GLFWwindow* window);

	bool MakeImageView(const VkDevice& device, const VKSurface& surface);

	std::vector<VkImage> GetImages(const VkDevice& device) const;

	std::pair<VkAttachmentDescription, VkAttachmentReference> GetAttachment();
};

