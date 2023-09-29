#pragma once
#include"Cube.h"
#include"../Vulkan/sampler/VKSampler.h"
#include"../Vulkan/buffer/VKUniformBuffers.h"
#include"../Vulkan/Data/MVP.h"
#include"../Vulkan/descriptor/VKDescriptor.h"

class TexturedCube
{
public:
	void Init();

	Cube cube;

	VKSampler sampler;

	VKUniformBuffers<MVP> mvpBuff;

	VKDescriptor descriptor;

	void draw(const VkCommandBuffer& commandBuff, uint32_t index);
};

