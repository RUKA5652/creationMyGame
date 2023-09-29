#pragma once
#include"../Vulkan/pipeline/shader/VkVertexShader.h"
#include"../Vulkan/Data/VertexUV.h"

class CubeShaderInfo :
	public VkVertexShader<VertexUV>
{
public:

private:
	void MakeInputAttribs() override;

};
