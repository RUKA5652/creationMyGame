#pragma once
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>
#include"../vma/vk_mem_alloc.h"

class VKImage
{
public:
	//�C���[�W���\�[�X
	VkImage image;
	//�C���[�W���\�[�X�ɂǂ̂悤�ȃt�H�[�}�b�g�ŃA�N�Z�X����̂�
	VkImageView imageView;
	/*
	VkDeviceMemory memory;

	void Release(const VkDevice& device);

	bool Init(const VkDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties,
		const VkImageCreateInfo& imageInfo, const VkImageViewCreateInfo viewInfo);
	/*/
	VmaAllocation allocation;

	void Release(const VmaAllocator& allocator);

	bool Init(const VkDevice& device,const VmaAllocator& allocator, const VmaAllocationCreateInfo& vmaAllocInfo, const VkImageCreateInfo& imageInfo, VkImageViewCreateInfo& viewInfo);
	//*/
	void SetImageMemoryBarrier(const VkCommandBuffer& command, const VkImageLayout& oldlayout,const VkImageLayout& newlayout);
};

