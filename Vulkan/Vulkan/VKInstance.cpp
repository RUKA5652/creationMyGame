#include "VKInstance.h"
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <iostream>
#include<algorithm>

//デバッグコールバック
//VkDebugUtilsMessageTypeFlagBitsEXT:メッセージの重要度
#ifdef _DEBUG
VKAPI_ATTR VkBool32 VKAPI_CALL VKInstance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        // メッセージは表示する必要があるほど重要
        std::cerr << "validation layer メッセージ: " << pCallbackData->pMessage << std::endl;
    }

    return VK_FALSE;
}
#endif // _DEBUG



bool VKInstance::Init(const char* appName)
{
#ifdef _DEBUG
    uint32_t ver;
    vkEnumerateInstanceVersion(&ver);

    uint32_t major = VK_VERSION_MAJOR(ver);
    uint32_t minor = VK_VERSION_MINOR(ver);
    uint32_t patch = VK_VERSION_PATCH(ver);

    std::cout << "Vulkan API version: " << major << "." << minor << "." << patch << std::endl;
#endif // _DEBUG

    //VkApplicationInfo設定
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    //アプリケーション名、バージョン
    appInfo.pApplicationName = appName;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    //エンジン名、バージョン
    appInfo.pEngineName = "Vulkan";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    //使用するVulkan のバージョン
    appInfo.apiVersion = VK_API_VERSION_1_3;

    //レイヤー,検証レイヤー有効化
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    //APP設定をセット
    createInfo.pApplicationInfo = &appInfo;
#ifdef _DEBUG

    //利用可能レイヤー格納し出力と存在するかチェック
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    std::cout << "利用可のレイヤー出力:" << std::endl;
    for (auto& layerName : availableLayers)
    {
        std::cout << '\t' << layerName.layerName << std::endl;
    }

    //利用可能レイヤーにあるかチェック
    bool checkFlag = false;
    for (auto& layerName : validationLayers)
    {
        checkFlag = std::ranges::any_of(availableLayers, [layerName](VkLayerProperties& name) {return std::strcmp(name.layerName, layerName) == 0; });
        if (!checkFlag)
        {
            std::cerr << layerName << ":存在しません" << std::endl;
        }
    }

    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
    //デバッグメッセンジャー
    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};
    debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    debugCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    debugCreateInfo.pfnUserCallback = debugCallback;
    createInfo.pNext = &debugCreateInfo;



#else 
    createInfo.enabledLayerCount = 0;
    createInfo.pNext = nullptr;
#endif // _DEBUG
    //グローバル拡張設定
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

#ifdef _DEBUG
    //拡張機能のサポートチェック
    uint32_t extensionCount = 0;
    //数を取得
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> vkExtensions(extensionCount);
    //格納
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, vkExtensions.data());
    //吐き出し
    std::cout << "利用可能な拡張機能:" << std::endl;
    for (const auto& extension : vkExtensions) {
        std::cout << '\t' << extension.extensionName << std::endl;
    }
    //拡張機能がサポートされているかどうか
    for (auto& extensionName : extensions)
    {
        if (!std::ranges::any_of(vkExtensions, [&](auto& vkExtension) {return  std::strcmp(vkExtension.extensionName, extensionName) == 0; }))
        {
            std::cout << "利用可能な拡張機能に該当なし:" << std::endl;
            std::cout << '\t' << extensionName << std::endl;
        }
    }
#endif // _DEBUG


    if (vkCreateInstance(&createInfo, nullptr, &instance) != VkResult::VK_SUCCESS)
    {
        //例外
        throw std::runtime_error("valkan instance 失敗");
        return false;
    }

    return true;
}
