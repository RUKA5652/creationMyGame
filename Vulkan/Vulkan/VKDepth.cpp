#include "VKDepth.h"
#include <stdexcept>
/*
bool VKDepth::Init(const VkDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties,const VKSwapchain& swapChain)
{

	VkImageCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	createInfo.imageType = VK_IMAGE_TYPE_2D;
	createInfo.format = VK_FORMAT_D32_SFLOAT;
	createInfo.extent = { .width{swapChain.extent.width},.height{swapChain.extent.height},.depth{1} };
	createInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	createInfo.arrayLayers = 1;
	createInfo.mipLevels = 1;
	


	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	//取得したイメージ
	viewInfo.image = image;
	//VkSurfaceFormatのformat
	viewInfo.format = VkFormat::VK_FORMAT_D32_SFLOAT;
	viewInfo.components = {
	VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G,
	VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A,
	};
	viewInfo.subresourceRange = { VK_IMAGE_ASPECT_DEPTH_BIT ,0, 1, 0, 1 };


	return VKImage::Init(device,memoryProperties,createInfo,viewInfo);
}
*/


bool VKDepth::Init(const VkDevice& device, const VmaAllocator& allocator, const VKSwapchain& swapChain)
{

	VkImageCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	createInfo.imageType = VK_IMAGE_TYPE_2D;
	createInfo.format = VK_FORMAT_D32_SFLOAT;
	createInfo.extent = { .width{swapChain.extent.width},.height{swapChain.extent.height},.depth{1} };
	createInfo.usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	createInfo.arrayLayers = 1;
	createInfo.mipLevels = 1;



	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	//取得したイメージ
	viewInfo.image = image;
	//VkSurfaceFormatのformat
	viewInfo.format = VkFormat::VK_FORMAT_D32_SFLOAT;
	viewInfo.components = {
	VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G,
	VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A,
	};
	viewInfo.subresourceRange = { VK_IMAGE_ASPECT_DEPTH_BIT ,0, 1, 0, 1 };

	VmaAllocationCreateInfo vmaAllocInfo{};
	vmaAllocInfo.usage = VMA_MEMORY_USAGE_AUTO;

	return VKImage::Init(device,allocator, vmaAllocInfo ,createInfo, viewInfo);
}

std::pair<VkAttachmentDescription, VkAttachmentReference> VKDepth::GetAttachment()
{
	VkAttachmentDescription depthTarget{};
	depthTarget.format = VK_FORMAT_D32_SFLOAT;
	depthTarget.samples = VK_SAMPLE_COUNT_1_BIT;
	depthTarget.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
	depthTarget.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
	depthTarget.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	depthTarget.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	depthTarget.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	depthTarget.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	VkAttachmentReference depthReference;
	depthReference.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	return { depthTarget,depthReference };
}
