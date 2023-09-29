#include "VKDepthStencil.h"

void VKDepthStencil::Init()
{
	createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	createInfo.depthTestEnable = VK_TRUE;
	createInfo.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
	createInfo.depthWriteEnable = VK_TRUE;
	createInfo.stencilTestEnable = VK_FALSE;
}
