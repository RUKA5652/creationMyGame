#pragma once
#include<vulkan/vulkan_core.h>
#include<vulkan/vk_layer.h>
#include"VKQueueFamilyIndex.h"

/// <summary>
/// コマンドプール
/// </summary>
class VKCommandPool
{
public:
	VkCommandPool commandPool;
	bool Init(const VkDevice& device,const VKQueueFamilyIndex& index);
};

