#pragma once
#include<vulkan/vulkan_core.h>
#include<vector>

class VKPipeline
{
public:
	VkPipeline pipeline;
	VkPipelineLayout layout;



	bool GraphicsInit(const VkDevice& device, const VkRenderPass& renderPass, VkPipeline& pipeline, 
		VkPipelineLayout& layout, const VkExtent2D& extent, const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages, const VkPipelineVertexInputStateCreateInfo* shaderInfo);

};

