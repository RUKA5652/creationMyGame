#pragma once
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>
#include<optional>

struct GetMemoryTypeIndex
{
	std::optional<uint32_t>  operator()(const VkPhysicalDeviceMemoryProperties& memoryProperties
		,uint32_t requestBits, VkMemoryPropertyFlags requestProps)
	{
		std::optional<uint32_t> memoryTypeIndex;
		for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; ++i)
		{
			if (requestBits & 1)
			{
				const auto& types = memoryProperties.memoryTypes[i];
				if ((types.propertyFlags & requestProps) == requestProps)
				{
					memoryTypeIndex = i; 
					break;
				}
			}
			requestBits >>= 1;
		}
		return memoryTypeIndex;

	};
};
