#pragma once
#include"VKImage.h"
#include"../buffer/VKBuffer.h"
#include"../stb/stb_image.h"
#include"../VKCommandBuffer.h"

/// <summary>
/// ‰æ‘œ
/// </summary>
class VKTexture:
	public VKImage
{
public:
	bool Init(const VkDevice& device, const VkCommandPool& commandPool, const VkQueue& queue, const VmaAllocator& allocator, const char* path);

	void CmdBind(const VkCommandBuffer& commandBuff, const VkDeviceSize& offset);
private:
	VKBuffer MakeStagingBuffer(const VmaAllocator& allocator, const int& texWid, const int& texHei, const stbi_uc* pImage,auto pImageSize);
	//“]‘—
	void TransferImage(VKCommandBuffer& commandBuffer, const VKBuffer& stagingBuffer, const int& texWid, const int& texHei);

};

