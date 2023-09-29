#pragma once
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>
#include"../vma/vk_mem_alloc.h"
class VKBuffer
{
public:
	VkBuffer buffer;
	/*
	VkDeviceMemory memory;
	void Release(const VkDevice& device);
	bool Init(const VkDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties, uint32_t size, VkBufferUsageFlags usage, VkMemoryPropertyFlagBits ubo);
	/*/
	VmaAllocation allocation;
	void Release(const VmaAllocator& allocator);
	bool Init(const VmaAllocator& allocator,uint32_t size, VkBufferUsageFlags usage, VmaAllocationCreateFlags flags, VkMemoryPropertyFlags requiredFlags, VkMemoryPropertyFlags preferredFlags, uint32_t vmaAllocationCreateFlagBits = 0, VmaMemoryUsage vmaUsage = VMA_MEMORY_USAGE_UNKNOWN);
	//*/
};

