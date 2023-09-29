#pragma once
#include"../Vulkan/buffer/VKVertexBuffer.h"
#include<array>
#include"../Vulkan/Data/Vertex.h"

class TriangleData:
	public VKVertexBuffer<Vertex>
{
public:
	TriangleData();

	void Init();

};

