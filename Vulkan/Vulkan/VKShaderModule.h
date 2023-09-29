#pragma once
#include<vulkan/vulkan_core.h>
#include"spv/spirv_reflect.h"

class VKShaderModule
{
public:
	VKShaderModule();
	VKShaderModule(const VkDevice& device,const char* fileName);
	~VKShaderModule();

	VkShaderModule shaderModule;

	void Load(const VkDevice& device,const char* fileName);

	const VkPipelineShaderStageCreateInfo& GetCreateInfo();
	const std::vector<VkDescriptorPoolSize>* GetDescriptorPool();
	const std::vector<VkDescriptorSetLayoutBinding>* GetLayoutBindings();

	void Destroyet(const VkDevice& device);

private:
	VkPipelineShaderStageCreateInfo createInfo_;
	std::vector<VkDescriptorPoolSize>* poolSizes_;
	std::vector<VkDescriptorSetLayoutBinding>* layoutBindings_;


	//spv解析
	SpvReflectShaderModule LoadSpv(size_t codeSize, const void* pCode);
	//シェーダモジュール作成
	void MakeShaderModule(const VkDevice& device, const std::vector<char>& data);
	//シェーダーステージの構成情報
	void MakePipelineShaderStageCreateInfo(const SpvReflectShaderModule& reflect);
	//デスクリプタを生成する情報
	void MakeDescriptorPoolSizes(const SpvReflectShaderModule& reflect);
	//バインディング情報作成
	void MakeDescriptorSetLayoutBindings(const SpvReflectShaderModule& reflect);

};

