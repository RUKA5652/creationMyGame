#pragma once
#include "../Vulkan/buffer/VKVertexBuffer.h"
#include"../Vulkan/Data/VertexUV.h"
#include"../Vulkan/image/VKTexture.h"

class Cube :
    public VKVertexBuffer<VertexUV>
{
public:
    Cube();

    VKTexture texture;

    void Init();
};

