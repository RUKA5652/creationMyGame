#pragma once
#include <vulkan/vk_layer.h>
#include<vector>

/// <summary>
/// �����f�o�C�X
/// </summary>
/// 
class VKPhysicalDevice
{
public:
	VKPhysicalDevice();
	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceMemoryProperties memoryProperties;
	bool Init(const VkInstance& instance);

	//�g���@�\
	const std::vector<const char*> deviceExtensions = {
	VK_KHR_SWAPCHAIN_EXTENSION_NAME,VK_KHR_GET_MEMORY_REQUIREMENTS_2_EXTENSION_NAME
	};


	bool SetPhysicalDevice(const VkInstance& instance);
	bool CheckDeviceExtensionSupport(const VkPhysicalDevice& device);
	


};

