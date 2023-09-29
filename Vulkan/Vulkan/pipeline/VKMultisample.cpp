#include "VKMultisample.h"

void VKMultisample::NoMultiSample()
{
	createInfo= {};
	createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	createInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
}
