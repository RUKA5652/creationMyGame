#pragma once
#include<vulkan/vulkan_core.h>
#include<vector>


class VKDescriptor
{
public:
	//VkDescriptorSet���Ǘ�����v�[��
	VkDescriptorPool pool;
	//���C�A�E�g��`
	VkDescriptorSetLayout layout;
	//���ۂɎg�����
	std::vector<VkDescriptorSet> descriptorSet;


	void PrepareDescriptorSet(const VkDevice& device,uint32_t size);

	bool CreateDescriptorPool(const VkDevice& device,uint32_t maxSize, std::vector<std::pair<const VkDescriptorPoolSize*, size_t>> poolSize);
	//VkDescriptorSetLayoutBinding�z�񂩂�SetLayout���쐬����
	bool MakeSetLayout(const VkDevice& device,std::vector<std::pair<const VkDescriptorSetLayoutBinding*,size_t>> layoutBindingsSet);

	//�X�V�f�[�^�ǉ�
	void AddWriteSet(VkWriteDescriptorSet& writeSet);

	//�X�V
	void Update(const VkDevice& device);
private:
	//�X�V�����Ɏg�����
	std::vector<VkWriteDescriptorSet> writeSet_;


};

