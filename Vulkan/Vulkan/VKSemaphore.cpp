#include "VKSemaphore.h"

void VKSemaphore::Init(const VkDevice& device)
{
	VkSemaphoreCreateInfo info{};
	info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	vkCreateSemaphore(device,&info,nullptr,&semphore);
}

void VKSemaphore::Destroy(const VkDevice& device)
{
	vkDestroySemaphore(device,semphore, nullptr);
}
