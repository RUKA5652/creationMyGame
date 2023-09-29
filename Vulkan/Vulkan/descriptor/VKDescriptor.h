#pragma once
#include<vulkan/vulkan_core.h>
#include<vector>


class VKDescriptor
{
public:
	//VkDescriptorSetを管理するプール
	VkDescriptorPool pool;
	//レイアウト定義
	VkDescriptorSetLayout layout;
	//実際に使うやつ
	std::vector<VkDescriptorSet> descriptorSet;


	void PrepareDescriptorSet(const VkDevice& device,uint32_t size);

	bool CreateDescriptorPool(const VkDevice& device,uint32_t maxSize, std::vector<std::pair<const VkDescriptorPoolSize*, size_t>> poolSize);
	//VkDescriptorSetLayoutBinding配列からSetLayoutを作成する
	bool MakeSetLayout(const VkDevice& device,std::vector<std::pair<const VkDescriptorSetLayoutBinding*,size_t>> layoutBindingsSet);

	//更新データ追加
	void AddWriteSet(VkWriteDescriptorSet& writeSet);

	//更新
	void Update(const VkDevice& device);
private:
	//更新処理に使うやつ
	std::vector<VkWriteDescriptorSet> writeSet_;


};

