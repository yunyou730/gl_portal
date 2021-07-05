#include "../../headers/ImGUI/AyyImGUI.h"

namespace ayy {

void ImGUIDelegate::Setup(GLFWwindow* window,const char* glslVersion)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glslVersion);
}

void ImGUIDelegate::OnFrameBegin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void ImGUIDelegate::OnFrameEnd()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGUIDelegate::Render()
{
//    ImGui::ShowDemoWindow();
    
//
//    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
//
//    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
//    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
//    ImGui::Checkbox("Another Window", &show_another_window);
//
////    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
////    ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color
//
//
//    ImGui::SameLine();
//    ImGui::Text("counter = %d", 111);
//
//    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
//    ImGui::End();
    
//    ImGui::Begin("Scene select");
//    ImGui::D
//    ImGui::End();
    

    
    if(_guiFunc != nullptr)
    {
        _guiFunc();
    }
}

void ImGUIDelegate::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImGUIDelegate::SetFuncCallback(const std::function<void()>& guiFunc)
{
    _guiFunc = guiFunc;
}

}
