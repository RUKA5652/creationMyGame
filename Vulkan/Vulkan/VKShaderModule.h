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


	//spv���
	SpvReflectShaderModule LoadSpv(size_t codeSize, const void* pCode);
	//�V�F�[�_���W���[���쐬
	void MakeShaderModule(const VkDevice& device, const std::vector<char>& data);
	//�V�F�[�_�[�X�e�[�W�̍\�����
	void MakePipelineShaderStageCreateInfo(const SpvReflectShaderModule& reflect);
	//�f�X�N���v�^�𐶐�������
	void MakeDescriptorPoolSizes(const SpvReflectShaderModule& reflect);
	//�o�C���f�B���O���쐬
	void MakeDescriptorSetLayoutBindings(const SpvReflectShaderModule& reflect);

};

