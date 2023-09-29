#include "VKCommandPool.h"
#include <stdexcept>


bool VKCommandPool::Init(const VkDevice& device, const VKQueueFamilyIndex& index)
{
	VkCommandPoolCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	createInfo.queueFamilyIndex = index.graphicsFamily.value();
	createInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	if (vkCreateCommandPool(device, &createInfo, nullptr, &commandPool) != VkResult::VK_SUCCESS)
	{
		throw std::runtime_error("コマンドプール作成失敗");
		return false;
	}
	return false;
}
