#include "TexturedCube.h"
#include "../Vulkan/VulkanAppBase.h"
#include "../Vulkan/VKShaderModule.h"
#include"CubeShaderInfo.h"
#include"../Vulkan/Data/MVP.h"
#include <glm/gtc/matrix_transform.hpp>


void TexturedCube::Init()
{
	sampler.Init(lpVkApp.GetVkDevice());

	cube.Init();

	mvpBuff.Init(lpVkApp.GetAllocator(), lpVkApp.GetVKSwapchain().imageView.size());

	//使うシェーダーを読み込む
	VKShaderModule vert(lpVkApp.GetVkDevice(), "GLSL/VertexShaderUV.vert.spv");
	VKShaderModule frag(lpVkApp.GetVkDevice(), "GLSL/PixelShaderUV.frag.spv");

	//ディスクリプタを作成
	descriptor.MakeSetLayout(lpVkApp.GetVkDevice(), { {vert.GetLayoutBindings()->data(),vert.GetLayoutBindings()->size()},
													{frag.GetLayoutBindings()->data(),frag.GetLayoutBindings()->size()} });

	descriptor.CreateDescriptorPool(lpVkApp.GetVkDevice(), mvpBuff.uniformBuffers.size(), { {vert.GetDescriptorPool()->data(),vert.GetDescriptorPool()->size()},
													{frag.GetDescriptorPool()->data(),frag.GetDescriptorPool()->size()} });

	descriptor.PrepareDescriptorSet(lpVkApp.GetVkDevice(), mvpBuff.uniformBuffers.size());

	//値を更新
	for (int i = 0; i < mvpBuff.uniformBuffers.size(); i++)
	{
		//値を書き込む命令を作成
		//mvp
		VkDescriptorBufferInfo mvpInfo{};
		mvpInfo.buffer = mvpBuff.uniformBuffers[i].buffer;
		mvpInfo.offset = 0;
		mvpInfo.range = VK_WHOLE_SIZE;
		VkWriteDescriptorSet mvpWriteSet{};
		mvpWriteSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		mvpWriteSet.dstBinding = 0;
		mvpWriteSet.descriptorCount = 1;
		mvpWriteSet.pBufferInfo = &mvpInfo;
		mvpWriteSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		mvpWriteSet.dstSet = descriptor.descriptorSet[i];
		descriptor.AddWriteSet(mvpWriteSet);
		//画像
		VkDescriptorImageInfo imageInfo{};
		imageInfo.imageView = cube.texture.imageView;
		imageInfo.sampler = sampler.sampler;
		imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
		VkWriteDescriptorSet imageWriteSet{};
		imageWriteSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		imageWriteSet.dstBinding = 1;
		imageWriteSet.descriptorCount = 1;
		imageWriteSet.pImageInfo = &imageInfo;
		imageWriteSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		imageWriteSet.dstSet = descriptor.descriptorSet[i];
		descriptor.AddWriteSet(imageWriteSet);

		//値を更新(適用)
		descriptor.Update(lpVkApp.GetVkDevice());
	}


	VkPipelineLayoutCreateInfo pipeCreateInfo{};
	pipeCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipeCreateInfo.setLayoutCount = 1;
	pipeCreateInfo.pSetLayouts = &descriptor.layout;
	lpVkApp.MakePipelineLayout(pipeCreateInfo);

	std::vector<VkPipelineShaderStageCreateInfo> shaderStages
	{
		vert.GetCreateInfo(),
		frag.GetCreateInfo()
	};

	CubeShaderInfo shaderInfo;
	shaderInfo.Init(lpVkApp.GetVkDevice());

	lpVkApp.MakeGraphicsPipeline(shaderStages, &shaderInfo.createInfo);

	lpVkApp.SetDrawCmd(std::bind_front(&TexturedCube::draw, this));

}

static glm::mat4 world = glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(0, 1, 0));
void TexturedCube::draw(const VkCommandBuffer& commandBuff, uint32_t index)
{

	//vkCmdBindPipeline(commandBuff, VK_PIPELINE_BIND_POINT_GRAPHICS, lpVkApp.GetVKPipeline().pipeline);

	 // ユニフォームバッファの中身を更新する.
	MVP shaderParam{};
	shaderParam.mtxWorld = world += glm::rotate(glm::identity<glm::mat4>(), glm::radians(45.0f), glm::vec3(0, 1, 0));
	shaderParam.mtxView = glm::lookAtRH(glm::vec3(0.0f, 3.0f, 5.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	shaderParam.mtxProj = glm::perspective(glm::radians(60.0f), 640.0f / 480, 0.01f, 100.0f);

	auto& allocator = lpVkApp.GetAllocator();
	auto allocation = mvpBuff.uniformBuffers[index].allocation;
	void* ptr = nullptr;
	vmaMapMemory(allocator, allocation, &ptr);
	memcpy(ptr, &shaderParam, sizeof(MVP));
	vmaUnmapMemory(allocator, allocation);


	// 作成したパイプラインをセット
	vkCmdBindPipeline(commandBuff, VK_PIPELINE_BIND_POINT_GRAPHICS, lpVkApp.GetVKPipeline().pipeline);

	// 各バッファオブジェクトのセット
	VkDeviceSize offset = 0;
	vkCmdBindVertexBuffers(commandBuff, 0, 1, &cube.verticesBuff.buffer, &offset);
	vkCmdBindIndexBuffer(commandBuff, cube.indicesBuff.buffer, offset, VK_INDEX_TYPE_UINT32);


	vkCmdBindDescriptorSets(commandBuff,
		VK_PIPELINE_BIND_POINT_GRAPHICS,
		lpVkApp.GetVKPipeline().layout, 0, 1,
		&descriptor.descriptorSet[index],
		0, nullptr);


	// 3角形描画
	vkCmdDrawIndexed(commandBuff, cube.indices.size(), 1, 0, 0, 0);
}
