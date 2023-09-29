#include"Vulkan/VulkanAppBase.h"
#include"DrawTriangle/TriangleDrwaApp.h"
#include"TexturedCube//TexturedCube.h"

constexpr uint32_t WindowWidth = 800;
constexpr uint32_t WindowHeight = 600;
constexpr auto AppTitle = "Vulkan";

#ifdef _DEBUG
int main()
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//エントリーポイント 
#endif // DEBUG
{
    //GLFW初期化
    glfwInit();
    //OpenGLコンテキストを作らないことを知らせる
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    //ウィンドウリサイズ
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    auto window = glfwCreateWindow(WindowWidth, WindowHeight, AppTitle, nullptr/*モニターを指定出来る*/, nullptr);
    // Vulkan 初 期 化
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
    // Vulkan 終 了
    theApp.Release();
    glfwTerminate();
	return 0;
}

