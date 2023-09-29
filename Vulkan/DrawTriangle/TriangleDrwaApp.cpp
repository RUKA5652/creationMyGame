#include "TriangleDrwaApp.h"
#include"../Vulkan/VKShaderModule.h"
#include"TraiangleShaderInfo.h"
#include"../Vulkan/pipeline/VKPrimitiveTopology.h"
#include"../Vulkan/pipeline/VKPipelineRasterization.h"
#include"../Vulkan/pipeline/VKDepthStencil.h"
#include"../Vulkan/pipeline/VKMultisample.h"
#include"../Vulkan/pipeline/VKViewport.h"
#include"../Vulkan/pipeline/VKColorBlend.h"

void TriangleDrwaApp::Init()
{
	triangleObj.Init();
	
	//�g���V�F�[�_�[��ǂݍ���
	VKShaderModule vert(lpVkApp.GetVkDevice(), "GLSL/VertexShader.vert.spv");
	VKShaderModule frag(lpVkApp.GetVkDevice(), "GLSL/PixelShader.frag.spv");

	std::vector<VkPipelineShaderStageCreateInfo> shaderStages
	{
		vert.GetCreateInfo(),
		frag.GetCreateInfo()
	};


	TraiangleShaderInfo shaderInfo;
	shaderInfo.Init(lpVkApp.GetVkDevice());

	lpVkApp.MakeGraphicsPipeline(shaderStages, &shaderInfo.createInfo);

	lpVkApp.SetDrawCmd(std::bind_front(&TriangleDrwaApp::draw, this));

}

void TriangleDrwaApp::draw(const VkCommandBuffer& commandBuff, uint32_t index)
{
	vkCmdBindPipeline(commandBuff, VK_PIPELINE_BIND_POINT_GRAPHICS, lpVkApp.GetVKPipeline().pipeline);

	//�I�u�W�F�N�g�Z�b�g
	VkDeviceSize offset = 0;
	triangleObj.CmdBind(commandBuff, offset);

}
