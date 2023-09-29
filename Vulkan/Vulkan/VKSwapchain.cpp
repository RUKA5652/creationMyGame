#include "VKSwapchain.h"
#include<algorithm>
#include<iostream>

bool VKSwapchain::Init(const VkDevice& device,const VKSurface& surface, const VKQueueFamilyIndex& queueFamilyIndex,GLFWwindow* window)
{
    format = surface.surfaceFormat.format;
    auto imageCount = (std::max)(2u,surface.surfaceCapabilities.minImageCount);
    auto extent = surface.surfaceCapabilities.currentExtent;
    if (extent.width == 0xffffffff || extent.height == 0xffffffff)
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);
        extent.width = static_cast<uint32_t>(width);
        extent.height = static_cast<uint32_t>(height);
    }

#ifdef _DEBUG
    std::cout << "�X���b�v�`�F�C��:" << std::endl;
    std::cout << '\t' << "imageCount:" << imageCount << std::endl;
    std::cout << '\t' << "extent:" << extent.width << "," << extent.height << std::endl;
#endif // _DEBUG



    std::set<uint32_t> uniqueQueueFamilies = queueFamilyIndex.GetUniqueQueueFamilies();

    VkSwapchainCreateInfoKHR createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = surface.surface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surface.surfaceFormat.format;
    createInfo.imageColorSpace = surface.surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.preTransform = surface.surfaceCapabilities.currentTransform;
    //���ڃ����_�����O����
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    /*
    ��U�ʂ̉摜�Ƀ����_�����O����ꍇ VK_IMAGE_USAGE_TRANSFER_DST_BIT
    */
    createInfo.imageArrayLayers = 1;
    createInfo.presentMode = surface.presentMode;
    createInfo.oldSwapchain = VK_NULL_HANDLE;
    createInfo.clipped = VK_TRUE;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    if (vkCreateSwapchainKHR(device, &createInfo, nullptr, &swapChain) != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateSwapchainKHR���s");
        return false;
    }
    this->extent = extent;

    return MakeImageView(device, surface);
}

bool VKSwapchain::MakeImageView(const VkDevice& device, const VKSurface& surface)
{
    auto images = GetImages(device);
    imageView.resize(images.size());
    for (int i = 0; i < images.size(); ++i)
    {
        VkImageViewCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
        //�擾�����C���[�W
        createInfo.image = images[i];
        //VkSurfaceFormat��format
        createInfo.format = surface.surfaceFormat.format;
        createInfo.components = {
        VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G,
        VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A,
        };
        createInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 1, 0, 1 };
        if(vkCreateImageView(device, &createInfo, nullptr, &imageView[i]) != VkResult::VK_SUCCESS)
        {
            //��O
            throw std::runtime_error("imageView ���s");
            return false;
        }
    }


    return true;
}

std::vector<VkImage> VKSwapchain::GetImages(const VkDevice& device) const
{
    uint32_t count;
    vkGetSwapchainImagesKHR(device, swapChain, &count, nullptr);
    std::vector<VkImage> images(count);
    vkGetSwapchainImagesKHR(device, swapChain, &count, images.data());
    return images;
}

std::pair<VkAttachmentDescription, VkAttachmentReference> VKSwapchain::GetAttachment()
{
    VkAttachmentDescription colorTarget{};
    colorTarget.format = format;
    colorTarget.samples = VK_SAMPLE_COUNT_1_BIT;
    colorTarget.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorTarget.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorTarget.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorTarget.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorTarget.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorTarget.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorReference{};
    colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    return {colorTarget,colorReference};
}
