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
		//��O
		throw std::runtime_error("�g���镨���f�o�C�X�Ȃ�");
		return false;
	}
	//�������v���p�e�B�擾
	vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);
	return true;
}

bool VKPhysicalDevice::CheckDeviceExtensionSupport(const VkPhysicalDevice& device)
{
	//�f�o�C�X�̋@�\�擾
	uint32_t extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount,availableExtensions.data());


	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	//�K�v�Ȋg���@�\���܂܂�Ă���̂��`�F�b�N
	for (const auto& extension : availableExtensions)
	{
		requiredExtensions.erase(extension.extensionName);
	}


	return requiredExtensions.empty();
}

bool VKPhysicalDevice::SetPhysicalDevice(const VkInstance& instance)
{
	//�f�o�C�X�̎擾
	uint32_t count = 0;
	vkEnumeratePhysicalDevices(instance, &count, nullptr);
	std::vector<VkPhysicalDevice> physicalDevices(count);
	vkEnumeratePhysicalDevices(instance, &count, physicalDevices.data());

	//�f�o�C�X�̊m�F
	for (auto& device : physicalDevices)
	{
		if (CheckDeviceExtensionSupport(device))
		{
			//����͏��߂Ɍ����������̂��g��
			physicalDevice = device;
			break;
		}
	}

	return physicalDevice != nullptr;
}
