#pragma once
#include <vulkan/vk_layer.h>
#include<vector>

/// <summary>
/// インスタンス
/// </summary>
class VKInstance
{
public:
	VkInstance instance;
	//Vkインスタンスハンドル作成
	bool Init(const char* appName);
#ifdef _DEBUG
	const std::vector<const char*> validationLayers = { "VK_LAYER_KHRONOS_validation" };
#endif // _DEBUG
private:
#ifdef _DEBUG
	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData);
#endif // _DEBUG
};

