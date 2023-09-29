#pragma once
#include <optional>
#include <vulkan/vk_layer.h>
#include <set>

/// <summary>
/// キューインデックス
/// </summary>
class VKQueueFamilyIndex
{
public:
    //グラフィックス
    std::optional<uint32_t> graphicsFamily;
    //プレゼンテーション
    //std::optional<uint32_t> presentFamily;

    //自身が全てのコマンドを処理できるデバイスかどうか
    bool isComplete();

    bool Init(const VkPhysicalDevice& device);

    std::set<uint32_t> GetUniqueQueueFamilies() const;
};

