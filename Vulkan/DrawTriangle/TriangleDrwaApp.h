#pragma once
#include"../Vulkan/VulkanAppBase.h"
#include"TriangleData.h"

class TriangleDrwaApp
{
public:
	void Init();
	TriangleData triangleObj;

	void draw(const VkCommandBuffer& commandBuff, uint32_t index);
};

