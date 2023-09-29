    #include "VKRenderPass.h"
#include <stdexcept>
#include<array>


bool VKRenderPass::Init(const VkDevice& device, std::vector<std::pair<VkAttachmentDescription, VkAttachmentReference>> color, std::pair<VkAttachmentDescription, VkAttachmentReference> depth)
{    
    //各処理をSubpassとして定義 (VkSubpassDescription 構造体)
    //サブパスで描画先となる情報 VkAttachmentReference 構造体
    //出⼒・関連リソースをアタッチメントと表現 (VkAttachmentDescription 構造体)

    std::vector<VkAttachmentDescription> attachments(color.size() + 1);
    for (int i = 0; i < color.size(); i++)
    {
        attachments[i] = std::move(color[i].first);
    }
    attachments[attachments.size() - 1] = std::move(depth.first);

    std::vector<VkAttachmentReference> colorReference(color.size());
    for (int i = 0; i < color.size(); i++)
    {
        colorReference[i] = std::move(color[i].second);
        colorReference[i].attachment = i;
    }
    depth.second.attachment = colorReference.size();

    VkSubpassDescription subpassDesc{};
    subpassDesc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpassDesc.colorAttachmentCount = colorReference.size();
    subpassDesc.pColorAttachments = colorReference.data();
    subpassDesc.pDepthStencilAttachment = &depth.second;

    //レンダーパス⽣成
    VkRenderPassCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    createInfo.attachmentCount = attachments.size();
    createInfo.pAttachments = attachments.data();
    createInfo.subpassCount = 1;
    createInfo.pSubpasses = &subpassDesc;


    if (vkCreateRenderPass(device, &createInfo, nullptr, &renderPass) != VkResult::VK_SUCCESS)
    {
        //例外
        throw std::runtime_error("レンダーパス作成 失敗");
        return false;
    }

    return true;
}

void VKRenderPass::Begin(const VkCommandBuffer& cmdBuff,const VkFramebuffer& frameBuff,const VkExtent2D extent)
{
    std::array<VkClearValue, 2> clearValue =
    {
        VkClearValue{1.0,1.0,1.0,0},
        VkClearValue{1.0,0.0}
    };

    VkRenderPassBeginInfo info{};
    info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    info.framebuffer = frameBuff;
    info.renderPass = renderPass;
    info.renderArea.offset = { 0,0 };
    info.renderArea.extent = extent;
    info.clearValueCount = clearValue.size();
    info.pClearValues = clearValue.data();

    vkCmdBeginRenderPass(cmdBuff,&info, VK_SUBPASS_CONTENTS_INLINE);
}

void VKRenderPass::End(const VkCommandBuffer& cmdBuff)
{
    vkCmdEndRenderPass(cmdBuff);
}
