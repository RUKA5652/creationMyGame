#include "VKInstance.h"
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <iostream>
#include<algorithm>

//�f�o�b�O�R�[���o�b�N
//VkDebugUtilsMessageTypeFlagBitsEXT:���b�Z�[�W�̏d�v�x
#ifdef _DEBUG
VKAPI_ATTR VkBool32 VKAPI_CALL VKInstance::debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
{
    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        // ���b�Z�[�W�͕\������K�v������قǏd�v
        std::cerr << "validation layer ���b�Z�[�W: " << pCallbackData->pMessage << std::endl;
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

    //VkApplicationInfo�ݒ�
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    //�A�v���P�[�V�������A�o�[�W����
    appInfo.pApplicationName = appName;
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    //�G���W�����A�o�[�W����
    appInfo.pEngineName = "Vulkan";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    //�g�p����Vulkan �̃o�[�W����
    appInfo.apiVersion = VK_API_VERSION_1_3;

    //���C���[,���؃��C���[�L����
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions;
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
    std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    //APP�ݒ���Z�b�g
    createInfo.pApplicationInfo = &appInfo;
#ifdef _DEBUG

    //���p�\���C���[�i�[���o�͂Ƒ��݂��邩�`�F�b�N
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    std::cout << "���p�̃��C���[�o��:" << std::endl;
    for (auto& layerName : availableLayers)
    {
        std::cout << '\t' << layerName.layerName << std::endl;
    }

    //���p�\���C���[�ɂ��邩�`�F�b�N
    bool checkFlag = false;
    for (auto& layerName : validationLayers)
    {
        checkFlag = std::ranges::any_of(availableLayers, [layerName](VkLayerProperties& name) {return std::strcmp(name.layerName, layerName) == 0; });
        if (!checkFlag)
        {
            std::cerr << layerName << ":���݂��܂���" << std::endl;
        }
    }

    extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
    createInfo.ppEnabledLayerNames = validationLayers.data();
    //�f�o�b�O���b�Z���W���[
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
    //�O���[�o���g���ݒ�
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

#ifdef _DEBUG
    //�g���@�\�̃T�|�[�g�`�F�b�N
    uint32_t extensionCount = 0;
    //�����擾
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> vkExtensions(extensionCount);
    //�i�[
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, vkExtensions.data());
    //�f���o��
    std::cout << "���p�\�Ȋg���@�\:" << std::endl;
    for (const auto& extension : vkExtensions) {
        std::cout << '\t' << extension.extensionName << std::endl;
    }
    //�g���@�\���T�|�[�g����Ă��邩�ǂ���
    for (auto& extensionName : extensions)
    {
        if (!std::ranges::any_of(vkExtensions, [&](auto& vkExtension) {return  std::strcmp(vkExtension.extensionName, extensionName) == 0; }))
        {
            std::cout << "���p�\�Ȋg���@�\�ɊY���Ȃ�:" << std::endl;
            std::cout << '\t' << extensionName << std::endl;
        }
    }
#endif // _DEBUG


    if (vkCreateInstance(&createInfo, nullptr, &instance) != VkResult::VK_SUCCESS)
    {
        //��O
        throw std::runtime_error("valkan instance ���s");
        return false;
    }

    return true;
}
