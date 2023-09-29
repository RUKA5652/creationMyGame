#include "VKViewport.h"

void VKViewport::Init(const VkExtent2D& extent)
{
	scissor = {};
	scissor =
	{
		{0,0},
		extent
	};
	viewport = {};
	viewport.x = 0;
	viewport.y = extent.height;
	viewport.height = -1.0f * extent.height;
	viewport.width = extent.width;
	viewport.maxDepth = 1.0;
	viewport.minDepth = 0.0;

	creatInfo = {};
	creatInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	creatInfo.scissorCount = 1;
	creatInfo.pScissors = &scissor;
	creatInfo.viewportCount = 1;
	creatInfo.pViewports = &viewport;

};
