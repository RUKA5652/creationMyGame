#include "VKTexture.h"
#include"../VulkanAppBase.h"


/*
bool VKTexture::Init(const VkDevice& device, const VkPhysicalDeviceMemoryProperties& memoryProperties, const char* path)
{
    int texWid, texHei;
    int channels = 0;
    auto* pImage = stbi_load(path, &texWid, &texHei, &channels, 0);
    
	VkImageCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	createInfo.imageType = VK_IMAGE_TYPE_2D;
	createInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
	createInfo.extent = { .width{static_cast<unsigned int>(texWid)},.height{static_cast<unsigned int>(texHei)},.depth{1} };
	createInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT  | VK_IMAGE_USAGE_SAMPLED_BIT;
	createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	createInfo.arrayLayers = 1;
	createInfo.mipLevels = 1;


	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	//取得したイメージ
	viewInfo.image = image;
	//VkSurfaceFormatのformat
	viewInfo.format = VkFormat::VK_FORMAT_R8G8B8A8_UNORM;
	viewInfo.components = {
	VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G,
	VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A,
	};
	viewInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT ,0, 1, 0, 1 };

	VKImage::Init(device, memoryProperties, createInfo, viewInfo);

	//グラフィックデータを写す
	VKBuffer stagingBuff;
	auto imageSize = texWid * texHei * sizeof(uint32_t);
	stagingBuff.Init(device, memoryProperties, imageSize,VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
	void* point;
	vkMapMemory(device, stagingBuff.memory, 0, VK_WHOLE_SIZE, 0, &point);
	memcpy(point, pImage,imageSize);
	vkUnmapMemory(device, stagingBuff.memory);



	stagingBuff.Release(device);
	stbi_image_free(pImage);
    return true;
}

*/
bool VKTexture::Init(const VkDevice& device, const VkCommandPool& commandPool,const VkQueue& queue, const VmaAllocator& allocator, const char* path)
{
	int texWid, texHei;
	int channels = 0;
	auto* pImage = stbi_load(path, &texWid, &texHei, &channels, 0);

	VkImageCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	createInfo.imageType = VK_IMAGE_TYPE_2D;
	createInfo.format = VK_FORMAT_R8G8B8A8_UNORM;
	createInfo.extent = { .width{static_cast<unsigned int>(texWid)},.height{static_cast<unsigned int>(texHei)},.depth{1} };
	createInfo.usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	createInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	createInfo.arrayLayers = 1;
	createInfo.mipLevels = 1;


	VkImageViewCreateInfo viewInfo{};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	//取得したイメージ
	viewInfo.image = image;
	//VkSurfaceFormatのformat
	viewInfo.format = VkFormat::VK_FORMAT_R8G8B8A8_UNORM;
	viewInfo.components = {
	VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G,
	VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A,
	};
	viewInfo.subresourceRange = { VK_IMAGE_ASPECT_COLOR_BIT ,0, 1, 0, 1 };

	VmaAllocationCreateInfo vmaAllocInfo{};
	vmaAllocInfo.usage = VMA_MEMORY_USAGE_AUTO;
	VKImage::Init(device,allocator, vmaAllocInfo,createInfo, viewInfo);
	//ステージングバッファを作成
	auto stagingBuff = MakeStagingBuffer(allocator,texWid,texHei,pImage,texWid*texHei*channels* sizeof(unsigned char));
	//コマンドバッファ作成
	VKCommandBuffer commandBuffer{};
	commandBuffer.Init(device, commandPool, 1);
	//転送
	TransferImage(commandBuffer, stagingBuff, texWid, texHei);
	//実行させる
	VkSubmitInfo submitInfo{};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer.commandBuffer[0];
	vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);

	vkDeviceWaitIdle(device);
	commandBuffer.Destroy(device, commandPool);
	stagingBuff.Release(allocator);
	stbi_image_free(pImage);
	return true;
}

VKBuffer VKTexture::MakeStagingBuffer(const VmaAllocator& allocator,const int& texWid,const int& texHei,const stbi_uc* pImage, auto pImageSize)
{
	VKBuffer stagingBuff{};
	uint32_t imageSize = pImageSize;
	//*
	stagingBuff.Init(allocator, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VMA_ALLOCATION_CREATE_MAPPED_BIT,
		VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT,VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	//メモリに書き込み
	VmaAllocationInfo inf{  };
	vmaGetAllocationInfo(allocator,stagingBuff.allocation,&inf);
	void* point = nullptr;
	vmaMapMemory(allocator, stagingBuff.allocation, &point);
	memcpy(point, pImage, imageSize);
	vmaUnmapMemory(allocator, stagingBuff.allocation);
	/*/
	stagingBuff.Init(lpVkApp.GetVkDevice(),lpVkApp.GetVKPhysicalDevice().memoryProperties, imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT);
	void* point;
	vkMapMemory(lpVkApp.GetVkDevice(), stagingBuff.memory, 0, VK_WHOLE_SIZE, 0, &point);
	memcpy(point, pImage, imageSize);
	vkUnmapMemory(lpVkApp.GetVkDevice(), stagingBuff.memory);
	//*/
	return std::move(stagingBuff);
}

void VKTexture::TransferImage(VKCommandBuffer& commandBuffer,const VKBuffer& stagingBuffer, const int& texWid, const int& texHei)
{
	VkBufferImageCopy copyRegion{};
	copyRegion.imageExtent = { uint32_t(texWid), uint32_t(texHei), 1 };
	copyRegion.imageSubresource = { VK_IMAGE_ASPECT_COLOR_BIT, 0, 0, 1 };

	//命令書き込み開始
	commandBuffer.Begin(0);
	SetImageMemoryBarrier(commandBuffer.commandBuffer[0], VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	//コピー
	vkCmdCopyBufferToImage(commandBuffer.commandBuffer[0], stagingBuffer.buffer, image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &copyRegion);
	SetImageMemoryBarrier(commandBuffer.commandBuffer[0], VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	//命令終わり
	commandBuffer.End(0);
}


void VKTexture::CmdBind(const VkCommandBuffer& commandBuff, const VkDeviceSize& offset)
{
	//vkCmdCopyBufferToImage(commandBuff,stagingBuff.buffer,image,)


}

