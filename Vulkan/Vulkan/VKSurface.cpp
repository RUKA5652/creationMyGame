#include "VKSurface.h"
#include<vector>
#include<algorithm>
#include <iostream>

bool VKSurface::Init(const VkInstance& instance, const VkPhysicalDevice& physicalDevice, VkFormat format, GLFWwindow*& window)
{
	glfwCreateWindowSurface(instance, window, nullptr, &surface);
	presentMode = VkPresentModeKHR::VK_PRESENT_MODE_FIFO_KHR;
	bool flag = SelectFormat(physicalDevice, format) &&
		SelectPresent(physicalDevice, presentMode);
	SetSurfaceCapabilities(physicalDevice);
	return flag;
}

bool VKSurface::SelectFormat(const VkPhysicalDevice& physicalDevice,VkFormat format)
{
	//�g����\���p�T�[�t�F�C�X����
	uint32_t count = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice,surface,&count,nullptr);
	std::vector<VkSurfaceFormatKHR> formats(count);
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &count, formats.data());
#ifdef _DEBUG
	//�g����T�[�t�F�C�X�o��
	std::cout << "���p�̃T�[�t�F�C�X�t�H�[�}�b�g�o��:" << std::endl;
	for (auto& checkFormat : formats)
	{
		std::cout << '\t' << checkFormat.format << std::endl;
	}
#endif // _DEBUG
	

	for (auto& checkFormat : formats)
	{
		if (checkFormat.format == format)
		{
			surfaceFormat = checkFormat;
			return true;
		}
	}

	return false;
}

bool VKSurface::SelectPresent(const VkPhysicalDevice& physicalDevice, VkPresentModeKHR present)
{
	uint32_t count = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count,nullptr );
	std::vector<VkPresentModeKHR> presents(count);
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &count, presents.data());
#ifdef _DEBUG
	//�g����Present�o��
	std::cout << "���p�\Present�̏o��:" << std::endl;
	for (auto& present : presents)
	{
		std::cout << '\t' << present << std::endl;
	}
#endif // _DEBUG

	return std::ranges::any_of(presents, [&](VkPresentModeKHR p) {return present == p; });
}

void VKSurface::SetSurfaceCapabilities(const VkPhysicalDevice& physicalDevice)
{
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, &surfaceCapabilities);
}
