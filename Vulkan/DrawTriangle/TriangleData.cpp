#include "TriangleData.h"
#include"../Vulkan/VulkanAppBase.h"

using namespace glm;

TriangleData::TriangleData()
{
	vertices = {
		{ vec3(-1.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f) },
		{ vec3(+1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f) },
		{ vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f) },
		{vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f)}
	};
	indices = { 0,1,2,0,1,3 };

}

void TriangleData::Init()
{
	/*
 	VKVertexBuffer::Init(lpVkApp.GetVkDevice(), lpVkApp.GetVKPhysicalDevice().memoryProperties);
	WriteMapMemory(lpVkApp.GetVkDevice());
	/*/
	VKVertexBuffer::Init(lpVkApp.GetAllocator());
	WriteMapMemory(lpVkApp.GetAllocator());
	//*/
}
