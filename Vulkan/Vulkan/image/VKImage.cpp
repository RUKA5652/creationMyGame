#include "VKImage.h"
#include <stdexcept>
#include"../utility/GetMemoryTypeIndex.h"
/*
void VKImage::Release(const VkDevice& device)
{
	vkFreeMemory(device, memory, nullptr);
}

bool VKImage::Init(const VkDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties, const VkImageCreateInfo& imageInfo, VkImageViewCreateInfo viewInfo)
{
	if (vkCreateImage(device, &imageInfo, nullptr, &image) != VkResult::VK_SUCCESS)
	{
		throw std::runtime_error("ImageçÏê¨é∏îs");
		return false;
	}

	//ÉÅÉÇÉääÑÇËìñÇƒ
	VkMemoryRequirements reqs;
	vkGetImageMemoryRequirements(device, image, &reqs);
	VkMemoryAllocateInfo allocateInfo{};
	allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocateInfo.allocationSize = reqs.size;
	allocateInfo.memoryTypeIndex = GetMemoryTypeIndex()(memoryProperties, reqs.memoryTypeBits, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT).value();
	if (vkAllocateMemory(device, &allocateInfo, nullptr, &memory) != VkResult::VK_SUCCESS)
	{
		throw std::runtime_error("AllocateMemoryé∏îs");
		return false;
	}
	if (vkBindImageMemory(device, image, memory, 0) != VkResult::VK_SUCCESS)
	{
		throw std::runtime_error("BindImageMemoryé∏îs");
		return false;
	}

	viewInfo.image = image;

	if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VkResult::VK_SUCCESS)
	{
		//ó·äO
		throw std::runtime_error("imageView é∏îs");
		return false;
	}

    return false;
}
/*/
void VKImage::Release(const VmaAllocator& allocator)
{
	vmaDestroyImage(allocator, image, allocation);
}

bool VKImage::Init(const VkDevice& device, const VmaAllocator& allocator, const VmaAllocationCreateInfo& vmaAllocInfo,const VkImageCreateInfo& imageInfo, VkImageViewCreateInfo& viewInfo)
{
	vmaCreateImage(allocator, &imageInfo, &vmaAllocInfo, &image, &allocation, nullptr);
	viewInfo.image = image;
	if (vkCreateImageView(device, &viewInfo, nullptr, &imageView) != VkResult::VK_SUCCESS)
	{
		//ó·äO
		throw std::runtime_error("imageView é∏îs");
		return false;
	}

	return true;
}
//*/

//ÉÅÉÇÉäÉoÉäÉA
void VKImage::SetImageMemoryBarrier(const VkCommandBuffer& command, const VkImageLayout& oldlayout, const VkImageLayout& newlayout)
{
	VkImageMemoryBarrier memoryBarrier{};
	memoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	memoryBarrier.oldLayout = oldlayout;
	memoryBarrier.newLayout = newlayout;
	memoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	memoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	memoryBarrier.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT ,0,1,0,1 };
	memoryBarrier.image = image;

	VkPipelineStageFlags srcStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
	VkPipelineStageFlags dstStage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;

	switch (oldlayout)
	{
	case VK_IMAGE_LAYOUT_UNDEFINED:
		memoryBarrier.srcAccessMask = 0;
		break;
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		memoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		srcStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	}

	switch (newlayout)
	{
	case VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL:
		memoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		dstStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	case VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL:
		memoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		srcStage = VK_PIPELINE_STAGE_TRANSFER_BIT;
		break;
	case VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL:
		memoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
		srcStage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
		break;
	}

	vkCmdPipelineBarrier(command, srcStage | VK_PIPELINE_STAGE_TRANSFER_BIT, dstStage, 0, 0, nullptr, 0, nullptr, 1, &memoryBarrier);
}

