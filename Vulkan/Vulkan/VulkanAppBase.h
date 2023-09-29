#pragma once
//Win64�̂�
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vk_layer.h>
#include <vulkan/vulkan_win32.h>
//Vulkan���C�u���������N
#pragma comment(lib, "vulkan-1.lib")
#include"vma/vk_mem_alloc.h"

#include<functional>


#include"VkInstance.h"
#include"VKPhysicalDevice.h"
#include"VKDevice.h"
#include "VKCommandPool.h"
#include"VKQueue.h"
#include"VKSurface.h"
#include"VKSwapchain.h"
#include"VKDepth.h"
#include"VKRenderPass.h"
#include"VKFrameBuffer.h"
#include"VKCommandBuffer.h"
#include"VKSemaphore.h"
#include"VKFence.h"
#include"VKPipeline.h"


#define lpVkApp  VulkanAppBase::GetInstance()

using DrawCmd = std::function<void(const VkCommandBuffer&, uint32_t)>;

class VulkanAppBase
{
public:

	static VulkanAppBase& GetInstance();

	//����
	virtual void Init(GLFWwindow* window, const char* appName);
	//�j��
	virtual void Release();
	//����
	virtual void Prepare();
	//�`��
	virtual void Render();

	void SetDrawCmd(DrawCmd func);

	void MakeGraphicsPipeline(const std::vector<VkPipelineShaderStageCreateInfo>& shaderStages, const VkPipelineVertexInputStateCreateInfo* shaderInfo);
	void MakePipelineLayout(const VkPipelineLayoutCreateInfo& createInfo);
	void MakePipeline(const VkGraphicsPipelineCreateInfo& createInfo);

	const VkDevice& GetVkDevice();
	const VKPhysicalDevice& GetVKPhysicalDevice();
	const VKSwapchain& GetVKSwapchain();
	const VkRenderPass& GetVkRenderPass();
	const VKPipeline& GetVKPipeline();
	const VmaAllocator& GetAllocator();
	const VkCommandPool& GetCommandPool();
	const VkQueue& GetVkQueue();
private:
	VulkanAppBase();
	virtual ~VulkanAppBase() { }

	VulkanAppBase(const VulkanAppBase&) = delete;
	VulkanAppBase& operator=(const VulkanAppBase&) = delete;
	VulkanAppBase(VulkanAppBase&&) = delete;
	VulkanAppBase& operator=(VulkanAppBase&&) = delete;

	//�`��R�}���h
	DrawCmd makeCommand_;
	//�C���X�^���Xhandle
	VKInstance instance_;

	//�����f�o�C�X
	VKPhysicalDevice physicalDevice_;
	//�_���f�o�C�X
	VKDevice device_;
	//�R�}���h�v�[��
	VKCommandPool commandPool_;
	//�T�[�t�F�C�X
	VKSurface surface_;
	//�X���b�v�`�F�C��
	VKSwapchain swapchain_;
	//�f�v�X�o�b�t�@
	VKDepth depthBuff_;
	//�����_�[�p�X
	VKRenderPass renderPass_;
	//�t���[���o�b�t�@
	VKFrameBuffer frameBuffer_;
	//�R�}���h�o�b�t�@
	VKCommandBuffer commandBuffer_;
	//�R�}���h�t�F���X
	VKFence commandFence;
	//�����_�[�Z�}�t�H
	VKSemaphore renderCompleted_;
	//�Z�}�t�H
	VKSemaphore presentCompleted_;
	//�C���[�W�C���f�b�N�X
	uint32_t imageIndex_;
	//�p�C�v���C��
	VKPipeline pipeline_;
	//�������A���P�[�^
	VmaAllocator allocator_;

	//vmaAllocator�쐬
	bool MakeVmaAllocator(const VkInstance& instance,const VkPhysicalDevice& physicalDevice,const VkDevice& device);

};

