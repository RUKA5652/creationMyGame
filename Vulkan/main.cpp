#include"Vulkan/VulkanAppBase.h"
#include"DrawTriangle/TriangleDrwaApp.h"
#include"TexturedCube//TexturedCube.h"

constexpr uint32_t WindowWidth = 800;
constexpr uint32_t WindowHeight = 600;
constexpr auto AppTitle = "Vulkan";

#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//�G���g���[�|�C���g 
#endif // DEBUG
{
    //GLFW������
    glfwInit();
    //OpenGL�R���e�L�X�g�����Ȃ����Ƃ�m�点��
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //�E�B���h�E���T�C�Y
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    auto window = glfwCreateWindow(WindowWidth, WindowHeight, AppTitle, nullptr/*���j�^�[���w��o����*/, nullptr);
    // Vulkan �� �� ��
    auto& theApp = lpVkApp;
    theApp.Init(window, AppTitle);

   //TriangleDrwaApp triangleApp;
   //triangleApp.Init();

    TexturedCube cube;
    cube.Init();

    while (glfwWindowShouldClose(window) == GLFW_FALSE)
    {
        glfwPollEvents();
        theApp.Render();
    }
    // Vulkan �I ��
    theApp.Release();
    glfwTerminate();
	return 0;
}

