#include "Cube.h"
#include "../Vulkan/VulkanAppBase.h"

using namespace glm;
Cube::Cube()
{
    const float k = 1.0f;
    const vec3 red(1.0f, 0.0f, 0.0f);
    const vec3 green(0.0f, 1.0f, 0.0f);
    const vec3 blue(0.0f, 0.0f, 1.0f);
    const vec3 white(1.0f);
    const vec3 black(0.0f);
    const vec3 yellow(1.0f, 1.0f, 0.0f);
    const vec3 magenta(1.0f, 0.0f, 1.0f);
    const vec3 cyan(0.0f, 1.0f, 1.0f);

    const vec2 lb(0.0f, 0.0f);
    const vec2 lt(0.0f, 1.0f);
    const vec2 rb(1.0f, 0.0f);
    const vec2 rt(1.0f, 1.0f);
    vertices = {
        // front
        // ê≥ñ .
        { vec3(-k, k, k), yellow,  lb },
        { vec3(-k,-k, k), red,     lt },
        { vec3(k, k, k), white,   rb },
        { vec3(k,-k, k), magenta, rt },
        // âE.
        { vec3(k, k, k), white,   lb },
        { vec3(k,-k, k), magenta, lt },
        { vec3(k, k,-k), cyan,    rb },
        { vec3(k,-k,-k), blue,    rt },
        // ç∂
        { vec3(-k, k,-k), green,  lb },
        { vec3(-k,-k,-k), black,  lt },
        { vec3(-k, k, k), yellow, rb },
        { vec3(-k,-k, k), red,    rt },
        // ó†.
        { vec3(k, k,-k), cyan, lb },
        { vec3(k,-k,-k), blue, lt },
        { vec3(-k, k,-k), green, rb },
        { vec3(-k,-k,-k), black, rt },
        // è„.
        { vec3(-k, k,-k), green, lb },
        { vec3(-k, k, k), yellow, lt },
        { vec3(k, k,-k), cyan, rb },
        { vec3(k, k, k), white, rt },
        // íÍ.
        { vec3(-k,-k, k), red, lb },
        { vec3(-k,-k,-k), black, lt },
        { vec3(k,-k, k), magenta, rb },
        { vec3(k,-k,-k), blue, rt },
    };
    indices = {
      0, 2, 1, 1, 2, 3, // front
      4, 6, 5, 5, 6, 7, // right
      8,10, 9, 9,10,11, // left

      12, 14, 13, 13, 14, 15, // back
      16, 18, 17, 17, 18, 19, // top
      20, 22, 21, 21, 22, 23, // bottom
    };

}

void Cube::Init()
{
	VKVertexBuffer::Init(lpVkApp.GetAllocator());
	WriteMapMemory(lpVkApp.GetAllocator());

    texture.Init(lpVkApp.GetVkDevice(), lpVkApp.GetCommandPool(),lpVkApp.GetVkQueue(), lpVkApp.GetAllocator(), "resource/ranking-A.png");

}
