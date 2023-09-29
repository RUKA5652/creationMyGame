#include "VKCommandBuffer.h"
#include <stdexcept>

bool VKCommandBuffer::Init(const VkDevice& device, const VkCommandPool& commandPool, uint32_t count)
{
    VkCommandBufferAllocateInfo allocateInfo{};
    allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocateInfo.commandPool = commandPool;
    allocateInfo.commandBufferCount = count;
    commandBuffer.resize(count);
    commandBuffer.shrink_to_fit();
    if(vkAllocateCommandBuffers(device, &allocateInfo, commandBuffer.data()) != VkResult::VK_SUCCESS)
    {
        throw std::runtime_error("AllocateInfoçÏê¨é∏îs");
        return false;
    }

    return true;    
}

void VKCommandBuffer::Begin(uint32_t index)
{
    VkCommandBufferBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    vkBeginCommandBuffer(commandBuffer[index], &info);
}

void VKCommandBuffer::End(uint32_t index)
{
    vkEndCommandBuffer(commandBuffer[index]);
}

void VKCommandBuffer::Destroy(const VkDevice& device, const VkCommandPool& commandPool)
{
    vkFreeCommandBuffers(device, commandPool, commandBuffer.size(), commandBuffer.data());
}
