#pragma once
#include"VKBuffer.h"
#include<vector>

template<class T>
class VKUniformBuffers
{
public:
	std::vector<VKBuffer> uniformBuffers;
	

	bool Init(const VmaAllocator& allocator, uint32_t count);

	

private:


};

template<class T>
inline bool VKUniformBuffers<T>::Init(const VmaAllocator& allocator, uint32_t count)
{
	uniformBuffers.resize(count);

	for (auto& buff : uniformBuffers)
	{
		buff.Init(allocator, sizeof(T), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VMA_ALLOCATION_CREATE_MAPPED_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,0);
	}

	return false;
}
