#pragma once
//Win64のみ
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define VK_USE_PLATFORM_WIN32_KHR
#define GLFW_INCLUDE_VULKAN
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <vulkan/vk_layer.h>
#include <vulkan/vulkan_win32.h>
//Vulkanライブラリリンク
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

	//生成
	virtual void Init(GLFWwindow* window, const char* appName);
	//破棄
	virtual void Release();
	//準備
	virtual void Prepare();
	//描画
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

	//描画コマンド
	DrawCmd makeCommand_;
	//インスタンスhandle
	VKInstance instance_;

	//物理デバイス
	VKPhysicalDevice physicalDevice_;
	//論理デバイス
	VKDevice device_;
	//コマンドプール
	VKCommandPool commandPool_;
	//サーフェイス
	VKSurface surface_;
	//スワップチェイン
	VKSwapchain swapchain_;
	//デプスバッファ
	VKDepth depthBuff_;
	//レンダーパス
	VKRenderPass renderPass_;
	//フレームバッファ
	VKFrameBuffer frameBuffer_;
	//コマンドバッファ
	VKCommandBuffer commandBuffer_;
	//コマンドフェンス
	VKFence commandFence;
	//レンダーセマフォ
	VKSemaphore renderCompleted_;
	//セマフォ
	VKSemaphore presentCompleted_;
	//イメージインデックス
	uint32_t imageIndex_;
	//パイプライン
	VKPipeline pipeline_;
	//メモリアロケータ
	VmaAllocator allocator_;

	//vmaAllocator作成
	bool MakeVmaAllocator(const VkInstance& instance,const VkPhysicalDevice& physicalDevice,const VkDevice& device);

};

