#include "VKPhysicalDevice.h"
#include<vector>
#include<string>
#include<set>
#include <iostream>

VKPhysicalDevice::VKPhysicalDevice()
{
	physicalDevice = nullptr;
}

bool VKPhysicalDevice::Init(const VkInstance& instance)
{
	if (!SetPhysicalDevice(instance))
	{
		//例外
		throw std::runtime_error("使える物理デバイスなし");
		return false;
	}
	//メモリプロパティ取得
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);
	return true;
}

bool VKPhysicalDevice::CheckDeviceExtensionSupport(const VkPhysicalDevice& device)
{
	//デバイスの機能取得
	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,availableExtensions.data());


	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	//必要な拡張機能が含まれているのかチェック
	for (const auto& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}


	return requiredExtensions.empty();
}

bool VKPhysicalDevice::SetPhysicalDevice(const VkInstance& instance)
{
	//デバイスの取得
	uint32_t count = 0;
	vkEnumeratePhysicalDevices(instance, &count, nullptr);
	std::vector<VkPhysicalDevice> physicalDevices(count);
	vkEnumeratePhysicalDevices(instance, &count, physicalDevices.data());

	//デバイスの確認
	for (auto& device : physicalDevices)
	{
		if (CheckDeviceExtensionSupport(device))
		{
			//今回は初めに見つかったものを使う
			physicalDevice = device;
			break;
		}
	}

	return physicalDevice != nullptr;
}
