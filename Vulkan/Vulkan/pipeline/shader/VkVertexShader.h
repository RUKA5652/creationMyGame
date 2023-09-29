#pragma once
#include<vulkan/vulkan_core.h> 
#include<vulkan/vk_layer.h>
#include<vector>

template<class T>
class VkVertexShader
{
public:

	VkVertexInputBindingDescription inputBinding;
	std::vector<VkVertexInputAttributeDescription> inputAttribs;
	VkPipelineVertexInputStateCreateInfo createInfo;

	void Init(const VkDevice& device);
protected:
	virtual void MakeInputAttribs() = 0;
};

template<class T>
inline void VkVertexShader<T>::Init(const VkDevice& device)
{
	inputBinding.binding = 0;
	inputBinding.stride = sizeof(T);
	inputBinding.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	MakeInputAttribs();
	createInfo={};
	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	//VkVertexInputBindingDescriptionÇÃêî 
	createInfo.vertexBindingDescriptionCount = 1;
	createInfo.pVertexBindingDescriptions = &inputBinding;
	createInfo.vertexAttributeDescriptionCount = inputAttribs.size();
	createInfo.pVertexAttributeDescriptions = inputAttribs.data();



}
