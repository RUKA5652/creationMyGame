#include "VKPipelineRasterization.h"

void VKPipelineRasterization::Init()
{
	createInfo = {};
	//�����v����\�ɂ���
	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	createInfo.polygonMode = VK_POLYGON_MODE_FILL;
	createInfo.cullMode = VK_CULL_MODE_NONE;
	createInfo.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
	createInfo.lineWidth = 1.0f;
}
