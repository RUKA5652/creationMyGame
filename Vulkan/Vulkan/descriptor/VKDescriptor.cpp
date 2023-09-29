#include "VKDescriptor.h"
#include <stdexcept>
#include <map>


void VKDescriptor::PrepareDescriptorSet(const VkDevice& device, uint32_t size)
{
    std::vector<VkDescriptorSetLayout> layouts;
    for (int i = 0; i< size; ++i)
    {
        layouts.push_back(layout);
    }
    VkDescriptorSetAllocateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    info.descriptorPool = pool;
    info.descriptorSetCount = size;
    info.pSetLayouts = layouts.data();
    descriptorSet.resize(size);
    vkAllocateDescriptorSets(device, &info, descriptorSet.data());

}

bool VKDescriptor::CreateDescriptorPool(const VkDevice& device, uint32_t maxSize, std::vector<std::pair<const VkDescriptorPoolSize*, size_t>> poolSize)
{
    //èWåv
    std::map<VkDescriptorType, int> typeCnt;
    for (auto& [data, cnt] : poolSize)
    {
        for (size_t i = 0; i < cnt; i++)
        {
            typeCnt.try_emplace(data[i].type, 0).first->second+= data[i].descriptorCount;
        }
    }
    //äiî[
    std::vector<VkDescriptorPoolSize> poolSizes_(typeCnt.size());
    int i = 0;
    for (auto& [type, cnt] : typeCnt)
    {
        poolSizes_[i].descriptorCount = cnt * maxSize;
        poolSizes_[i].type = static_cast<VkDescriptorType>(type);
        i++;
    }
    //çÏê¨
    VkDescriptorPoolCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    info.maxSets = maxSize;
    info.poolSizeCount = uint32_t(poolSizes_.size());
    info.pPoolSizes = poolSizes_.data();

    if(vkCreateDescriptorPool(device, &info, nullptr, &pool) != VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateDescriptorPoolé∏îs");
        return false;
    }
    return true;
}

bool VKDescriptor::MakeSetLayout(const VkDevice& device, std::vector<std::pair<const VkDescriptorSetLayoutBinding*, size_t>> layoutBindingsSet)
{

    size_t size = 0;
    for (auto& [vec,cnt] : layoutBindingsSet)
    {
        size += cnt;
    }
    std::vector<VkDescriptorSetLayoutBinding> mergedBindings(size);
    for (size_t i = 0 , cnt = 0 ; cnt < size; i++)
    {
        auto& vec = layoutBindingsSet[i].first;
        auto& vecSize = layoutBindingsSet[i].second;
        for (rsize_t j = 0; j < vecSize; j++)
        {
            mergedBindings[cnt++] = vec[j];
        }
    }
    VkDescriptorSetLayoutCreateInfo info{};
    info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    info.bindingCount = uint32_t(mergedBindings.size());
    info.pBindings = mergedBindings.data();


    if (vkCreateDescriptorSetLayout(device, &info, nullptr, &layout) != VK_SUCCESS)
    {
        throw std::runtime_error("vkCreateDescriptorSetLayouté∏îs");
        return false;
    }
    return true;
}

void VKDescriptor::AddWriteSet(VkWriteDescriptorSet& writeSet)
{
    writeSet_.push_back(writeSet);
}

void VKDescriptor::Update(const VkDevice& device)
{
    vkUpdateDescriptorSets(device,writeSet_.size(), writeSet_.data(),0,nullptr);
    writeSet_.clear();
}
