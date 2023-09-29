#include "TraiangleShaderInfo.h"

void TraiangleShaderInfo::MakeInputAttribs()
{

	inputAttribs = {
		// location, binding, format, offset
		VkVertexInputAttributeDescription{0,0,VK_FORMAT_R32G32B32_SFLOAT,offsetof(Vertex,pos)},
		VkVertexInputAttributeDescription{1,0,VK_FORMAT_R32G32B32_SFLOAT,offsetof(Vertex,color)}
	};

}
 