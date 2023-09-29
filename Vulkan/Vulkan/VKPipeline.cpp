#include "VKPipeline.h"
#include"pipeline/VKPrimitiveTopology.h"
#include"pipeline/VKPipelineRasterization.h"
#include"pipeline/VKDepthStencil.h"
#include"pipeline/VKMultisample.h"
#include"pipeline/VKViewport.h"
#include"pipeline/VKColorBlend.h"
#include <stdexcept>


bool VKPipeline::GraphicsInit(const VkDevice& device, const  VkRenderPass& renderPass, VkPipeline& pipeline, VkPipelineLayout& layout, const VkExtent2D& extent, const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages, const VkPipelineVertexInputStateCreateInfo* shaderInfo)
{
	VKPrimitiveTopology inputAssembly;
	inputAssembly.Triangle();

	VKPipelineRasterization rasterization;
	rasterization.Init();

	VKDepthStencil depthStencil;
	depthStencil.Init();

	VKMultisample multisample;
	multisample.NoMultiSample();

	VKViewport viewport;
	viewport.Init(extent);

	VKColorBlend colorBlend;
	colorBlend.Init();

	if (!layout)
	{
		VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo{};
		pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		vkCreatePipelineLayout(device, &pipelineLayoutCreateInfo, nullptr, &layout);
	}


	//パイプラインの構築
	VkGraphicsPipelineCreateInfo createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	createInfo.stageCount = uint32_t(shaderStages.size());
	createInfo.pStages = shaderStages.data();
	createInfo.pInputAssemblyState = &inputAssembly.createInfo;
	createInfo.pVertexInputState = shaderInfo;
	createInfo.pRasterizationState = &rasterization.createInfo;
	createInfo.pDepthStencilState = &depthStencil.createInfo;
	createInfo.pMultisampleState = &multisample.createInfo;
	createInfo.pViewportState = &viewport.creatInfo;
	createInfo.pColorBlendState = &colorBlend.createInfo;
	createInfo.renderPass = renderPass;
	createInfo.layout = layout;

	if (vkCreateGraphicsPipelines(device, VK_NULL_HANDLE, 1, &createInfo, nullptr, &pipeline) != VK_SUCCESS)
	{
		throw std::runtime_error("MakePipeline失敗");
	}

	return true;
}
