#include "VKShaderModule.h"
#include<fstream>
#include<vector>
#include<map>

VKShaderModule::VKShaderModule()
{
    poolSizes_ = nullptr;
    layoutBindings_ = nullptr;
}

VKShaderModule::VKShaderModule(const VkDevice& device, const char* fileName)
{
    Load(device, fileName);
}

VKShaderModule::~VKShaderModule()
{
    delete poolSizes_;
    delete layoutBindings_;
}

void VKShaderModule::Load(const VkDevice& device,const char* fileName)
{
    
    //ファイルを開く
    std::ifstream file(fileName,std::ios::binary);
    if (!file)
    {
        throw std::runtime_error("ファイルが開けない");
    }
    //ファイルからデータを取り出す
    std::vector<char> data(static_cast<size_t>(file.seekg(0, std::ifstream::end).tellg()));
    file.seekg(0, std::ifstream::beg).read(data.data(), data.size());
    //spv解析
    auto reflect = LoadSpv(data.size(), data.data());
    //シェーダモジュール作成
    MakeShaderModule(device, data);

    MakePipelineShaderStageCreateInfo(reflect);

    MakeDescriptorPoolSizes(reflect);

    MakeDescriptorSetLayoutBindings(reflect);

    //開放する
    spvReflectDestroyShaderModule(&reflect);
}

const VkPipelineShaderStageCreateInfo& VKShaderModule::GetCreateInfo()
{
    return createInfo_;
}

const std::vector<VkDescriptorPoolSize>* VKShaderModule::GetDescriptorPool()
{
    return poolSizes_;
}

const std::vector<VkDescriptorSetLayoutBinding>* VKShaderModule::GetLayoutBindings()
{
    return layoutBindings_;
}

void VKShaderModule::Destroyet(const VkDevice& device)
{
    delete[] createInfo_.pName;
    vkDestroyShaderModule(device, shaderModule, nullptr);
    delete poolSizes_;
    poolSizes_ = nullptr;
    delete layoutBindings_;
    layoutBindings_ = nullptr;
}

void VKShaderModule::MakeShaderModule(const VkDevice& device,const std::vector<char>& data)
{
    //シェーダーモジュール作成
    VkShaderModuleCreateInfo shCreateInfo{};
    shCreateInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    shCreateInfo.pCode = reinterpret_cast<const uint32_t*>(data.data());
    shCreateInfo.codeSize = data.size();
    vkCreateShaderModule(device, &shCreateInfo, nullptr, &shaderModule);
}

void VKShaderModule::MakePipelineShaderStageCreateInfo(const SpvReflectShaderModule& reflect)
{
    createInfo_.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    createInfo_.stage = static_cast<VkShaderStageFlagBits>(reflect.shader_stage);
    createInfo_.module = shaderModule;
    //エントリーポイント
    rsize_t size = strlen(reflect.entry_point_name) + 1;
    auto name = new char[size];
    strcpy_s(name,(rsize_t)size, reflect.entry_point_name);
    createInfo_.pName = name;
}

void VKShaderModule::MakeDescriptorPoolSizes(const SpvReflectShaderModule& reflect)
{
    std::map<SpvReflectDescriptorType, int> typeCnt;
    
    for (int i = 0; i < reflect.descriptor_binding_count; i++)
    {
        typeCnt.try_emplace(reflect.descriptor_bindings[i].descriptor_type,0).first->second++;
    }
    poolSizes_ = new std::vector<VkDescriptorPoolSize>(typeCnt.size());
    int i = 0;
    for (auto& [type,cnt] : typeCnt)
    {
        (*poolSizes_)[i].descriptorCount = cnt;
        (*poolSizes_)[i].type = static_cast<VkDescriptorType>(type);
        i++;
    }
}

void VKShaderModule::MakeDescriptorSetLayoutBindings(const SpvReflectShaderModule& reflect)
{
    layoutBindings_ = new std::vector<VkDescriptorSetLayoutBinding>(reflect.descriptor_binding_count);

    for (int i = 0; i < layoutBindings_->size(); i++)
    {
        (*layoutBindings_)[i].binding = reflect.descriptor_bindings[i].binding;
        (*layoutBindings_)[i].descriptorType = static_cast<VkDescriptorType>(reflect.descriptor_bindings[i].descriptor_type);
        (*layoutBindings_)[i].descriptorCount = 1;
        (*layoutBindings_)[i].stageFlags = static_cast<VkShaderStageFlagBits>(reflect.shader_stage);
    }

}


SpvReflectShaderModule VKShaderModule::LoadSpv(size_t codeSize,const void* pCode)
{
    SpvReflectShaderModule reflect;
    if (spvReflectCreateShaderModule(codeSize, pCode, &reflect) != VK_SUCCESS)
    {
        throw std::runtime_error("spv解析失敗");
    }
    return std::move(reflect);
}
