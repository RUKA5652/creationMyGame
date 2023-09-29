#pragma once
#include <optional>
#include <vulkan/vk_layer.h>
#include <set>

/// <summary>
/// �L���[�C���f�b�N�X
/// </summary>
class VKQueueFamilyIndex
{
public:
    //�O���t�B�b�N�X
    std::optional<uint32_t> graphicsFamily;
    //�v���[���e�[�V����
    //std::optional<uint32_t> presentFamily;

    //���g���S�ẴR�}���h�������ł���f�o�C�X���ǂ���
    bool isComplete();

    bool Init(const VkPhysicalDevice& device);

    std::set<uint32_t> GetUniqueQueueFamilies() const;
};

