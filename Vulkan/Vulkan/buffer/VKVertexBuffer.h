#pragma once
#include"VKBuffer.h"
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>
#include<glm/glm.hpp>
#include<vector>

template<class T>
class VKVertexBuffer
{
public:
	std::vector<T> vertices;
	std::vector<uint32_t> indices;

    VKBuffer verticesBuff;
    VKBuffer indicesBuff;
    /*
	bool Init(const VkDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties);

	bool WriteMapMemory(const VkDevice& device);
    /*/
    bool Init(const VmaAllocator& allocator);

    bool WriteMapMemory(const VmaAllocator& allocator);
    //*
    void CmdBind(const VkCommandBuffer& commandBuff, const VkDeviceSize& offset);

};
/*
template<class T>
inline bool VKVertexBuffer<T>::Init(const VkDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties)
{
    return verticesBuff.Init(device, memoryProperties, vertices.size() * sizeof(T), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) &&
        indicesBuff.Init(device, memoryProperties, indices.size() * sizeof(uint32_t), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
}

template<class T>
inline bool VKVertexBuffer<T>::WriteMapMemory(const VkDevice& device)
{
    void* verPtr = nullptr;
    vkMapMemory(device, verticesBuff.memory, 0, VK_WHOLE_SIZE, 0, &verPtr);
    memcpy(verPtr, vertices.data(), vertices.size() * sizeof(T));
    vkUnmapMemory(device, verticesBuff.memory);
    void* indexPtr = nullptr;
    vkMapMemory(device, indicesBuff.memory, 0, VK_WHOLE_SIZE, 0, &indexPtr);
    memcpy(indexPtr, indices.data(), indices.size() * sizeof(uint32_t));
    vkUnmapMemory(device, indicesBuff.memory);

    return true;
}
/*/
template<class T>
inline bool VKVertexBuffer<T>::Init(const VmaAllocator& allocator)
{
    return verticesBuff.Init(allocator, vertices.size() * sizeof(T), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VMA_ALLOCATION_CREATE_MAPPED_BIT,VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) &&
        indicesBuff.Init(allocator, indices.size() * sizeof(uint32_t), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VMA_ALLOCATION_CREATE_MAPPED_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
}

template<class T>
inline bool VKVertexBuffer<T>::WriteMapMemory(const VmaAllocator& allocator)
{
    void* verPtr = nullptr;
    vmaMapMemory(allocator,verticesBuff.allocation, &verPtr);
    memcpy(verPtr, vertices.data(), vertices.size() * sizeof(T));
    vmaUnmapMemory(allocator, verticesBuff.allocation);
    void* indexPtr = nullptr;
    vmaMapMemory(allocator, indicesBuff.allocation, &indexPtr);
    memcpy(indexPtr, indices.data(), indices.size() * sizeof(T));
    vmaUnmapMemory(allocator, indicesBuff.allocation);
    return false;
}
//*

template<class T>
inline void VKVertexBuffer<T>::CmdBind(const VkCommandBuffer& commandBuff, const VkDeviceSize& offset)
{
    vkCmdBindVertexBuffers(commandBuff, 0, 1, &verticesBuff.buffer, &offset);
    vkCmdBindIndexBuffer(commandBuff, indicesBuff.buffer, offset,VK_INDEX_TYPE_UINT32);
    //•` ‰æ
    vkCmdDrawIndexed(commandBuff, indices.size(), 1, 0, 0, 0);
}
