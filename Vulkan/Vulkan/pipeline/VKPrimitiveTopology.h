#pragma once
#include<vulkan/vulkan_core.h>

/// <summary>
/// �v���~�e�B�u�g�|���W�[
/// �`�悷��}�`�̊�{�`��
/// </summary>
class VKPrimitiveTopology
{
public:
	VkPipelineInputAssemblyStateCreateInfo createInfo;
	void Triangle();
};

