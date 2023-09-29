#pragma once
#include<vulkan/vulkan_core.h>

/// <summary>
/// プリミティブトポロジー
/// 描画する図形の基本形状
/// </summary>
class VKPrimitiveTopology
{
public:
	VkPipelineInputAssemblyStateCreateInfo createInfo;
	void Triangle();
};

