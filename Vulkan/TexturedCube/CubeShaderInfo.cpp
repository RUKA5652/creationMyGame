#include "CubeShaderInfo.h"

void CubeShaderInfo::MakeInputAttribs()
{
	inputAttribs = {
		// location, binding, format, offset
		VkVertexInputAttributeDescription{0,0,VK_FORMAT_R32G32B32_SFLOAT,offsetof(VertexUV,pos)},
		VkVertexInputAttributeDescription{1,0,VK_FORMAT_R32G32B32_SFLOAT,offsetof(VertexUV,color)},
		VkVertexInputAttributeDescription{2,0,VK_FORMAT_R32G32B32_SFLOAT,offsetof(VertexUV,uv)}
	};

}
