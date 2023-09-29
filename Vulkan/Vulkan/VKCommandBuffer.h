#pragma once
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>
#include<vector>

class VKCommandBuffer
{
public:
	std::vector<VkCommandBuffer> commandBuffer;
	bool Init(const VkDevice& device,const VkCommandPool& commandPool,uint32_t count);

	void Begin(uint32_t index);

	void End(uint32_t index);

	void Destroy(const VkDevice& device, const VkCommandPool& commandPool);

};

