#pragma once
#include <vulkan/vk_layer.h>
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>


class VKSurface
{
public:
	VkSurfaceKHR surface;
	VkSurfaceFormatKHR surfaceFormat;
	VkSurfaceCapabilitiesKHR surfaceCapabilities;
	VkPresentModeKHR presentMode;
	bool Init(const VkInstance& instance,const VkPhysicalDevice& physicalDevice, VkFormat format,GLFWwindow*& window);
	bool SelectFormat(const VkPhysicalDevice& physicalDevice,VkFormat format);
	bool SelectPresent(const VkPhysicalDevice& physicalDevice,VkPresentModeKHR present);
	void SetSurfaceCapabilities(const VkPhysicalDevice& physicalDevice);
};

