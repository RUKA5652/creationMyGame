#include "VKBuffer.h"
#include"../utility/GetMemoryTypeIndex.h"
#include <stdexcept>
#include"../vma/vk_mem_alloc.h"

/*/
void VKBuffer::Release(const VkDevice& device)
{
    vkFreeMemory(device, memory,nullptr);
}

bool VKBuffer::Init(const VkDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties, uint32_t size, VkBufferUsageFlags usage, VkMemoryPropertyFlagBits ubo)
{
    VkBufferCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;

    createInfo.usage = usage;
    createInfo.size = size;

    vkCreateBuffer(device, &createInfo, nullptr, &buffer);
    //������
    VkMemoryRequirements reqs{};
    //�v���擾
    vkGetBufferMemoryRequirements(device, buffer, &reqs);

    VkMemoryAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    allocateInfo.allocationSize = reqs.size;
    allocateInfo.memoryTypeIndex = GetMemoryTypeIndex()(memoryProperties,reqs.memoryTypeBits, ubo).value();

    if (vkAllocateMemory(device, &allocateInfo, nullptr, &memory) != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("AllocateMemory���s");
        return false;
    }

    if (vkBindBufferMemory(device, buffer, memory, 0) != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("BindBufferMemory���s");
        return false;
    }
  


    return true;
}
/*/
void VKBuffer::Release(const VmaAllocator& allocator)
{
    vmaDestroyBuffer(allocator, buffer, allocation);
}

bool VKBuffer::Init(const VmaAllocator& allocator, uint32_t size, VkBufferUsageFlags usage, VmaAllocationCreateFlags flags, VkMemoryPropertyFlags requiredFlags, VkMemoryPropertyFlags preferredFlags, uint32_t vmaAllocationCreateFlagBits, VmaMemoryUsage vmaUsage)
{
    VkBufferCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    createInfo.usage = usage;
    createInfo.size = size;
    VmaAllocationCreateInfo allocationInfo{};
    allocationInfo.usage = vmaUsage;
    allocationInfo.flags = flags;
    allocationInfo.preferredFlags = preferredFlags;
    allocationInfo.requiredFlags = requiredFlags;
    allocationInfo.memoryTypeBits = vmaAllocationCreateFlagBits;
    if (vmaCreateBuffer(allocator, &createInfo, &allocationInfo, &buffer, &allocation, nullptr) != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("VMA�o�b�t�@���s");
        return false;
    }

    return true;
}
//*/

