#pragma once
#include"../Vulkan/pipeline/shader/VkVertexShader.h"
#include"../Vulkan/Data/Vertex.h"

class TraiangleShaderInfo:
	public VkVertexShader<Vertex>
{
public:

private:
	void MakeInputAttribs() override;

};

