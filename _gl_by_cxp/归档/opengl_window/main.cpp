#include<glad.h>
#include<glfw3.h>
#include<iostream>
#include<math.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include"shader.h"
#include"Model.h"
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>
#include<filesystem>
#include"imgui/imgui.h"
#include"imgui/imgui_impl_glfw.h"
#include"imgui/imgui_impl_opengl3.h"
#include"imgui/imgui.cpp"
#include"imgui/imgui_impl_glfw.cpp"
#include"imgui/imgui_impl_opengl3.cpp"
#include"imgui/imgui_draw.cpp"
#include"imgui/imgui_internal.h"
#include"imgui/imgui_widgets.cpp"
#include"imgui/imgui_demo.cpp"



void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path);
//bool up(GLFWwindow *window);
//bool down(GLFWwindow *window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadCubeMap(vector<std::string> cubemap_faces);
// settings
//unsigned int SCR_WIDTH = 2560;
//unsigned int SCR_HEIGHT = 1600;
glm::vec3 cameraPos=glm::vec3(0.0f,0.0f,3.0f);
glm::vec3 cameraFront=glm::vec3(0.0f,0.0f,-1.0f);
glm::vec3 cameraUp=glm::vec3(0.0f,1.0f,0.0f);
float deltatime=0.0f;
float lastframe=0.0f;
bool firstmouse=true;
float lastx=350.0f,lasty=350.0f;
float pitch=0.0f,yaw=0.0f;
float sensitivity=0.05f;
glm::vec3 lightPos(1.2f,1.0f,2.0f);

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
        
    // glfw window creation//full screen
    // --------------------
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();//get primary monitor
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    //glfwGetVideoMode:returns the current video mode of the specified monitor.
    //GLFWvidmode:The width & height, in screen coordinates, of the video mode.
    glfwWindowHint(GLFW_RED_BITS, mode->redBits);
    glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
    glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
    glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
    //glfwWindowHint(GLFW_SAMPLES, 4);//MSAA
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "MyEngine", monitor, NULL);//The desired width/height, in screen coordinates, of the window.
    int currentwidth, currentheight;
    glfwGetWindowSize(window, &currentwidth, &currentheight);
    glfwGetFramebufferSize(window, &currentwidth, &currentheight);//retrieve the size of the framebuffer of the window in pixels.
    
    const unsigned int SCR_WIDTH=currentwidth;//the width size of a framebuffer in pixels
    const unsigned int SCR_HEIGHT=currentheight;//the height size of a framebuffer in pixels
    const float SCR_OFFSET_W=1.0 / currentwidth;// 1/2560
    const float SCR_OFFSET_H=1.0 / currentheight;// 1/1600
    
    std::cout << "mode->width: "<<mode->width<<std::endl;
    std::cout << "mode->height: "<<mode->height<<std::endl;
    std::cout << "getwindowsize_width: "<<currentwidth<<std::endl;
    std::cout << "getwindowsize_height: "<<currentheight<<std::endl;
    
    //GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MyEngine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
        
    //初始化imgui
    ImGui::CreateContext();
    ImGuiIO &io=ImGui::GetIO();(void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");
    
    
    //定义一个imvec4来存储颜色值
    ImVec4 pointlightcolor_0_ingui=ImVec4(1.0f,0.0f,1.0f,1.0f);
    ImVec4* colorpointer0=&pointlightcolor_0_ingui;
    ImVec4 pointlightcolor_1_ingui=ImVec4(1.0f,0.0f,0.0f,1.0f);
    ImVec4* colorpointer1=&pointlightcolor_1_ingui;
    ImVec4 pointlightcolor_2_ingui=ImVec4(0.0f,0.0f,1.0f,1.0f);
    ImVec4* colorpointer2=&pointlightcolor_2_ingui;
    ImVec4 pointlightcolor_3_ingui=ImVec4(0.0f,1.0f,0.0f,1.0f);
    ImVec4* colorpointer3=&pointlightcolor_3_ingui;
    ImVec4 directlightcolor_ingui=ImVec4(1.0f,1.0f,1.0f,1.0f);
    ImVec4* directlight_pointer=&directlightcolor_ingui;
    ImVec4 clearcolor_ingui=ImVec4(0.1f,0.1f,0.1f,1.0f);
    ImVec4* clearcolorpointer=&clearcolor_ingui;
    ImVec4 outlinecolor_ingui=ImVec4(1.0f,1.0f,1.0f,1.0f);
    ImVec4* outlinecolorpointer=&outlinecolor_ingui;
    
    
//    //test
//    const char *vertexShaderSource_01 ="#version 330 core\n"
//        "layout (location = 0) in vec3 aPos;\n"
//        "layout (location = 1) in vec2 atexcoord;\n"
//        "out vec2 texcoord;\n"
//        "void main()\n"
//        "{\n"
//        "   gl_Position = vec4(aPos, 1.0);\n"
//        "   texcoord = atexcoord;\n"
//        "}\0";
//
//    const char *fragmentShaderSource_01 = "#version 330 core\n"
//        "out vec4 FragColor;\n"
//        "in vec2 texcoord;\n"
//        "uniform sampler2D texture_plane\n"
//        "void main()\n"
//        "{\n"
//        "   FragColor = texture(texture_plane,texcoord);\n"
//        "}\n\0";
//    unsigned int vertexShader_01 = glCreateShader(GL_VERTEX_SHADER);
//        glShaderSource(vertexShader_01, 1, &vertexShaderSource_01, NULL);
//        glCompileShader(vertexShader_01);
//        // check for shader compile errors
//        int success;
//        char infoLog[512];
//        glGetShaderiv(vertexShader_01, GL_COMPILE_STATUS, &success);
//        if (!success)
//        {
//            glGetShaderInfoLog(vertexShader_01, 512, NULL, infoLog);
//            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//        }
//        // fragment shader
//        unsigned int fragmentShader_01 = glCreateShader(GL_FRAGMENT_SHADER);
//        glShaderSource(fragmentShader_01, 1, &fragmentShaderSource_01, NULL);
//        glCompileShader(fragmentShader_01);
//        // check for shader compile errors
//        glGetShaderiv(fragmentShader_01, GL_COMPILE_STATUS, &success);
//        if (!success)
//        {
//            glGetShaderInfoLog(fragmentShader_01, 512, NULL, infoLog);
//            std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//        }
//        // link shaders
//        unsigned int shaderProgram_01 = glCreateProgram();
//        glAttachShader(shaderProgram_01, vertexShader_01);
//        glAttachShader(shaderProgram_01, fragmentShader_01);
//        glLinkProgram(shaderProgram_01);
//        // check for linking errors
//        glGetProgramiv(shaderProgram_01, GL_LINK_STATUS, &success);
//        if (!success) {
//            glGetProgramInfoLog(shaderProgram_01, 512, NULL, infoLog);
//            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//        }
//        glDeleteShader(vertexShader_01);
//        glDeleteShader(fragmentShader_01);
//        unsigned int texturebox = loadTexture("/Users/devilpxce/Desktop/textures/alphabox.png");
////        glActiveTexture(GL_TEXTURE15);
////        glBindTexture(GL_TEXTURE_2D, texturebox);
//        glUseProgram(shaderProgram_01);
//        glUniform1i(glGetUniformLocation(shaderProgram_01, "texture_plane"), 0);
    
    

//    float vertices_01[] = {
//             0.7f,  0.7f, 0.0f, 1.0f,1.0f, // top right
//             0.7f, -0.7f, 0.0f, 1.0f,0.0f, // bottom right
//            -0.7f, -0.7f, 0.0f, 0.0f,0.0f,// bottom left
//            -0.7f,  0.7f, 0.0f, 0.0f,1.0f  // top left
//        };
//        unsigned int indices_01[] = {  // note that we start from 0!
//            0, 1, 3,  // first Triangle
//            1, 2, 3   // second Triangle
//        };
//
//    unsigned int VBO_01, VAO_01, EBO_01;
//        glGenVertexArrays(1, &VAO_01);
//        glGenBuffers(1, &VBO_01);
//        glGenBuffers(1, &EBO_01);
//        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//        glBindVertexArray(VAO_01);
//
//        glBindBuffer(GL_ARRAY_BUFFER, VBO_01);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_01), vertices_01, GL_STATIC_DRAW);
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_01);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_01), indices_01, GL_STATIC_DRAW);
//
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//        glEnableVertexAttribArray(0);
//        // color attribute
//        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//        glEnableVertexAttribArray(1);


        // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
        // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
        glBindVertexArray(0);
//    //test
    
    
    
    
    
    
    //glEnable(GL_DEPTH_TEST);
    Shader modelshader("/Users/devilpxce/Desktop/shaders/model.vs","/Users/devilpxce/Desktop/shaders/model.fs");
    
    Shader model_ref_shader("/Users/devilpxce/Desktop/shaders/model.vs","/Users/devilpxce/Desktop/shaders/model_ref.fs");
    
    Shader model_refr_shader("/Users/devilpxce/Desktop/shaders/model.vs","/Users/devilpxce/Desktop/shaders/model_refr.fs");
    
    //定义light模型顶点数据//cube
    float vertices_light[] = {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };
    //绑定light相关VBO,VAO
    unsigned int lightVAO,VBO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_light), vertices_light, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };
    
    unsigned int quadVAO, quadVBO;
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    
    glm::vec3 pointLightPositions[4] = {
        glm::vec3( 0.7f,  0.1f,  2.0f),
        glm::vec3( -0.7f, 0.1f, 2.0f),
        glm::vec3(0.7f,  0.1f, -2.0f),
        glm::vec3( -0.7f,0.2f, -2.0f)
    };
    
    glm::vec3 pointLightColors[4] = {
        glm::vec3(1.0f,0.0f,1.0f),
        glm::vec3(1.0f,0.0f,0.0f),
        glm::vec3(0.0f,0.0f,1.0f),
        glm::vec3(0.0f,1.0f,1.0f)
    };
     

    modelshader.use();
    
    modelshader.set1float("spotlight.cos_cutoff_in", glm::cos(glm::radians(12.5f)));
    modelshader.set1float("spotlight.cos_cutoff_out", glm::cos(glm::radians(17.5f)));
    modelshader.set1float("spotlight.constant", 1.0f);
    modelshader.set1float("spotlight.linear", 0.045f);
    modelshader.set1float("spotlight.quadratic", 0.0075f);
    modelshader.setvec3("spotlight.ambient", glm::vec3(0.1f,0.1f,0.1f));
    modelshader.setvec3("spotlight.diffuse", glm::vec3(0.4f,0.4f,0.4f));
    modelshader.setvec3("spotlight.specular", glm::vec3(1.0f,1.0f,1.0f));
    
    //glm::vec3 dirlightcolor=glm::vec3(1.0f,1.0f,1.0f);
    modelshader.setvec3("dirlight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
    modelshader.setvec3("dirlight.ambient", glm::vec3(0.2f,0.2f,0.2f));
    modelshader.setvec3("dirlight.diffuse", glm::vec3(0.4f,0.4f,0.4f));
    modelshader.setvec3("dirlight.specular",glm::vec3(0.5f,0.5f,0.5f));
    
    modelshader.setvec3("pointlights[0].position", pointLightPositions[0]);
    modelshader.setvec3("pointlights[0].ambient",pointLightColors[0]*0.1f);
    modelshader.setvec3("pointlights[0].diffuse",pointLightColors[0]*0.2f);
    modelshader.setvec3("pointlights[0].specular",pointLightColors[0]*0.5f);
    modelshader.set1float("pointlights[0].constant", 1.0f);
    modelshader.set1float("pointlights[0].linear", 0.045f);
    modelshader.set1float("pointlights[0].quadratic", 0.0075f);
    
    modelshader.setvec3("pointlights[1].position", pointLightPositions[1]);
    modelshader.setvec3("pointlights[1].ambient",pointLightColors[1]*0.1f);
    modelshader.setvec3("pointlights[1].diffuse",pointLightColors[1]*0.2f);
    modelshader.setvec3("pointlights[1].specular",pointLightColors[1]*0.5f);
    modelshader.set1float("pointlights[1].constant", 1.0f);
    modelshader.set1float("pointlights[1].linear", 0.045f);
    modelshader.set1float("pointlights[1].quadratic", 0.0075f);
    
    modelshader.setvec3("pointlights[2].position", pointLightPositions[2]);
    modelshader.setvec3("pointlights[2].ambient",pointLightColors[2]*0.1f);
    modelshader.setvec3("pointlights[2].diffuse",pointLightColors[2]*0.2f);
    modelshader.setvec3("pointlights[2].specular",pointLightColors[2]*0.5f);
    modelshader.set1float("pointlights[2].constant", 1.0f);
    modelshader.set1float("pointlights[2].linear", 0.045f);
    modelshader.set1float("pointlights[2].quadratic", 0.0075f);
    
    modelshader.setvec3("pointlights[3].position", pointLightPositions[3]);
    modelshader.setvec3("pointlights[3].ambient",pointLightColors[3]*0.1f);
    modelshader.setvec3("pointlights[3].diffuse",pointLightColors[3]*0.2f);
    modelshader.setvec3("pointlights[3].specular",pointLightColors[3]*0.5f);
    modelshader.set1float("pointlights[3].constant", 1.0f);
    modelshader.set1float("pointlights[3].linear", 0.045f);
    modelshader.set1float("pointlights[3].quadratic", 0.0075f);
    
    modelshader.setbool("outline_vert", false);
    modelshader.setbool("outline_frag", false);
    
    Shader lightshader("/Users/devilpxce/Desktop/shaders/object.vs","/Users/devilpxce/Desktop/shaders/light.fs");
    
    
    Shader sharpen_shader("/Users/devilpxce/Desktop/shaders/frame.vs","/Users/devilpxce/Desktop/shaders/frame.fs");
    sharpen_shader.use();
    sharpen_shader.setint("screenTexture", 0);
    sharpen_shader.setvec2("TexSize", glm::vec2(SCR_OFFSET_W,SCR_OFFSET_H));
    
    Shader dout_shader("/Users/devilpxce/Desktop/shaders/direct_out.vs","/Users/devilpxce/Desktop/shaders/direct_out.fs");
    dout_shader.use();
    dout_shader.setint("screenTexture", 0);
    
    Shader zbuffer_shader("/Users/devilpxce/Desktop/shaders/direct_out.vs","/Users/devilpxce/Desktop/shaders/zbuffer.fs");
    dout_shader.use();
    dout_shader.setint("screenTexture", 0);
    
    
    
    //const std::string modelpath="/Users/devilpxce/Desktop/nanosuit_reflection/nanosuit.obj";
    //const std::string modelpath_penguin="/Users/devilpxce/Desktop/penguin/penguin.obj";
    //const std::string modelpath_robo="/Users/devilpxce/Desktop/T_RoBo/T_RoBo.obj";
    const std::string spherepath="/Users/devilpxce/Desktop/sphere/A.obj";
    const std::string modelpath="/Users/devilpxce/Desktop/spaceship/spaceship.obj";
    Model nanosuit(modelpath);
    Model sphere(spherepath);
    //Model penguin(modelpath_robo);
    
    
    glm::vec4 clearcolor(0.1f,0.1f,0.1f,1.0f);//定义初始化背景颜色
    

    bool outline_ornot=false;
    bool sharpen_on=false;
    bool z_on=false;
    bool reflect_on=false;
    bool refract_on=false;
    bool sphere_effectoff=false;
    
    
    //定义一个帧缓冲
    unsigned int framebuffer;
    glGenFramebuffers(1,&framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
    
    //创建颜色纹理并绑定到帧缓冲
    unsigned int texColorBuffer;
    glGenTextures(1,&texColorBuffer);
    glBindTexture(GL_TEXTURE_2D,texColorBuffer);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,(float)SCR_WIDTH,(float)SCR_HEIGHT,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);//以像素为单位定义图片宽高

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);
    
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,texColorBuffer,0);
    
    //render depth & stencil value to a texture to display
    unsigned int texDSBuffer;
    glGenTextures(1,&texDSBuffer);
    glBindTexture(GL_TEXTURE_2D,texDSBuffer);
  glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH24_STENCIL8,(float)SCR_WIDTH,(float)SCR_HEIGHT,0,GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8,NULL);//定义GL_TEXTURE_2D
    glBindTexture(GL_TEXTURE_2D,0);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_TEXTURE_2D,texDSBuffer,0);
    
    /*
    //定义用于动态映射的帧缓冲
    unsigned int cube_frame[6] = {
        cubeframe_right,
        cubeframe_left,
        cubeframe_top,
        cubeframe_bottom,
        cubeframe_front,
        cubeframe_back
    };
    unsigned int cube_frametex[6] = {
        cubeframetex_right,
        cubeframetex_left,
        cubeframetex_top,
        cubeframetex_bottom,
        cubeframetex_front,
        cubeframetex_back,
    };
    unsigned int cube_frametexDS[6] = {
        cubeframetexDS_right,
        cubeframetexDS_left,
        cubeframetexDS_top,
        cubeframetexDS_bottom,
        cubeframetexDS_front,
        cubeframetexDS_back,
    };
    */
    /*
    for(unsigned int i=0;i<6;i++){
         glGenFramebuffers(1,&cube_frame[i]);
         glBindFramebuffer(GL_FRAMEBUFFER,cube_frame[i]);
          
          //创建颜色纹理并绑定到帧缓冲
          //unsigned int texColorBuffer;
          glGenTextures(1,&cube_frametex[i]);
          glBindTexture(GL_TEXTURE_2D,cube_frametex[i]);
          glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,(float)SCR_HEIGHT,(float)SCR_HEIGHT,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);//以像素为单位定义图片宽高

          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
          glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
          glBindTexture(GL_TEXTURE_2D,0);
          
          glFramebufferTexture2D(GL_FRAMEBUFFER,GL_COLOR_ATTACHMENT0,GL_TEXTURE_2D,cube_frametex[i],0);
          
          //render depth & stencil value to a texture to display
          //unsigned int texDSBuffer;
          glGenTextures(1,&cube_frametexDS[i]);
          glBindTexture(GL_TEXTURE_2D,cube_frametexDS[i]);
        glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH24_STENCIL8,(float)SCR_HEIGHT,(float)SCR_HEIGHT,0,GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8,NULL);//定义GL_TEXTURE_2D
          glBindTexture(GL_TEXTURE_2D,0);
          glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_TEXTURE_2D,cube_frametexDS[i],0);
    };
    */
    /*
     //render depth & stencil value to a rbo
    //创建渲染缓冲对象并绑定到帧缓冲
    unsigned int rbo;//render buffer object
    glGenRenderbuffers(1,&rbo);
    glBindRenderbuffer(GL_RENDERBUFFER,rbo);
    glRenderbufferStorage(GL_RENDERBUFFER,GL_DEPTH24_STENCIL8,(float)SCR_WIDTH,(float)SCR_HEIGHT);//Specifies the width/height of the renderbuffer, in pixels.
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);
    */
    
    //check the completion of fbo
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER)!=GL_FRAMEBUFFER_COMPLETE)
        std::cout << "error:framebuffer not compelete" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER,0);//定义之后解绑
    //glFramebufferRenderbuffer(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_RENDERBUFFER,rbo);
    
    
//    vector<std::string> cubemapfaces{
//        "/Users/devilpxce/Desktop/skybox_1/right.png",
//        "/Users/devilpxce/Desktop/skybox_1/left.png",
//        "/Users/devilpxce/Desktop/skybox_1/top.png",
//        "/Users/devilpxce/Desktop/skybox_1/bottom.png",
//        "/Users/devilpxce/Desktop/skybox_1/front.png",
//        "/Users/devilpxce/Desktop/skybox_1/back.png"
//    };
    //glPixelStorei(GL_UNPACK_ALIGNMENT,1);
//    vector<std::string> cubemapfaces{
//        "/Users/devilpxce/Desktop/skybox_3/right.png",
//        "/Users/devilpxce/Desktop/skybox_3/left.png",
//        "/Users/devilpxce/Desktop/skybox_3/top.png",
//        "/Users/devilpxce/Desktop/skybox_3/bottom.png",
//        "/Users/devilpxce/Desktop/skybox_3/front.png",
//        "/Users/devilpxce/Desktop/skybox_3/back.png"
//    };
//    vector<std::string> cubemapfaces{
//        "/Users/devilpxce/Desktop/skybox/right.png",
//        "/Users/devilpxce/Desktop/skybox/left.png",
//        "/Users/devilpxce/Desktop/skybox/top.png",
//        "/Users/devilpxce/Desktop/skybox/bottom.png",
//        "/Users/devilpxce/Desktop/skybox/front.png",
//        "/Users/devilpxce/Desktop/skybox/back.png"
//    };
//
    vector<std::string> cubemapfaces{
        "/Users/devilpxce/Desktop/skybox_2/right.png",
        "/Users/devilpxce/Desktop/skybox_2/left.png",
        "/Users/devilpxce/Desktop/skybox_2/top.png",
        "/Users/devilpxce/Desktop/skybox_2/bottom.png",
        "/Users/devilpxce/Desktop/skybox_2/front.png",
        "/Users/devilpxce/Desktop/skybox_2/back.png"
    };
    
    unsigned int cubemapTexture=loadCubeMap(cubemapfaces);
    Shader cubemapshader("/Users/devilpxce/Desktop/shaders/cubemap.vs","/Users/devilpxce/Desktop/shaders/cubemap.fs");
    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };
    unsigned int cubemap_vao, cubemap_vbo;
    glGenVertexArrays(1, &cubemap_vao);
    glGenBuffers(1, &cubemap_vbo);
    glBindVertexArray(cubemap_vao);
    glBindBuffer(GL_ARRAY_BUFFER, cubemap_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
    //z-test exersice
    float vertices_z[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    unsigned int box_vao, box_vbo;
    glGenVertexArrays(1, &box_vao);
    glGenBuffers(1, &box_vbo);
    glBindVertexArray(box_vao);
    glBindBuffer(GL_ARRAY_BUFFER, box_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_z), vertices_z, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    
//    Shader alphabox_shader("/Users/devilpxce/Desktop/shaders/alphabox.vs","/Users/devilpxce/Desktop/shaders/alphabox.fs");
    Shader alphabox_shader("/Users/devilpxce/Desktop/shaders/alphabox1.vs","/Users/devilpxce/Desktop/shaders/alphabox1.fs");
//    unsigned int texturebox = loadTexture("/Users/devilpxce/Desktop/textures/alphabox.png");
//penguin use shader model_ztest
    //Shader ztest_shader("/Users/devilpxce/Desktop/shaders/model_ztest.vs","/Users/devilpxce/Desktop/shaders/model_ztest.fs");
    
    
    
    
    
//    alphabox_shader.use();
//    alphabox_shader.setint("texture_box", 0);
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, texturebox);
//    alphabox_shader.setint("texture1", 1);
    //alphabox_shader.setint("texture1", 0);
//    unsigned int texturebox;
//       // texture 1
//       // ---------
//       glGenTextures(1, &texturebox);
//       glBindTexture(GL_TEXTURE_2D, texturebox);
//       // set the texture wrapping parameters
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//       // set texture filtering parameters
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//       // load image, create texture and generate mipmaps
//       int width, height, nrChannels;
//       stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
//       unsigned char *data=stbi_load("/Users/devilpxce/Desktop/textures/alphabox.png", &width, &height, &nrChannels, 0);
//       if (data)
//       {
//           glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//           glGenerateMipmap(GL_TEXTURE_2D);
//       }
//       else
//       {
//           std::cout << "Failed to load texture1" << std::endl;
//       }
//       stbi_image_free(data);
//
//    alphabox_shader.use();
//    glActiveTexture(GL_TEXTURE1);
//    glBindTexture(GL_TEXTURE_2D, texturebox);
//    alphabox_shader.setint("texture1", 1);
   //z-test
    
    
    
    
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        //渲染到cube_frame[6]
        processInput(window);
        glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
   
        if(outline_ornot==true)
        {
            glEnable(GL_STENCIL_TEST);
            glEnable(GL_DEPTH_TEST);
            glDepthFunc(GL_LESS);
            //glEnable(GL_CULL_FACE);
            glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
            glClearColor(clearcolor.x,clearcolor.y,clearcolor.z,clearcolor.w);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
            glStencilMask(0x00);//绘制imgui时需要关闭模版测试写入
        }
        if(outline_ornot==false)
        {
        glClearColor(clearcolor.x,clearcolor.y,clearcolor.z,clearcolor.w);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        }
        
        float currentframe=glfwGetTime();
        deltatime=currentframe-lastframe;
        lastframe=currentframe;

        clearcolor=glm::vec4(clearcolorpointer->x,clearcolorpointer->y,clearcolorpointer->z,clearcolorpointer->w);
        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        modelshader.use();
        
        glm::vec3 point_color_0(colorpointer0->x,colorpointer0->y,colorpointer0->z);
        pointLightColors[0]=point_color_0;
        modelshader.setvec3("pointlights[0].ambient", point_color_0*0.1f);
        modelshader.setvec3("pointlights[0].diffuse", point_color_0*0.2f);
        modelshader.setvec3("pointlights[0].specular", point_color_0*1.0f);
        glm::vec3 point_color_1(colorpointer1->x,colorpointer1->y,colorpointer1->z);
        pointLightColors[1]=point_color_1;
        modelshader.setvec3("pointlights[1].ambient", point_color_1*0.1f);
        modelshader.setvec3("pointlights[1].diffuse", point_color_1*0.2f);
        modelshader.setvec3("pointlights[1].specular", point_color_1*1.0f);
        glm::vec3 point_color_2(colorpointer2->x,colorpointer2->y,colorpointer2->z);
        pointLightColors[2]=point_color_2;
        modelshader.setvec3("pointlights[2].ambient", point_color_2*0.1f);
        modelshader.setvec3("pointlights[2].diffuse", point_color_2*0.2f);
        modelshader.setvec3("pointlights[2].specular", point_color_2*1.0f);
        glm::vec3 point_color_3(colorpointer3->x,colorpointer3->y,colorpointer3->z);
        pointLightColors[3]=point_color_3;
        modelshader.setvec3("pointlights[3].ambient", point_color_3*0.1f);
        modelshader.setvec3("pointlights[3].diffuse", point_color_3*0.2f);
        modelshader.setvec3("pointlights[3].specular", point_color_3*1.0f);
        glm::vec3 directlightcolor(directlight_pointer->x,directlight_pointer->y,directlight_pointer->z);
        modelshader.setvec3("dirlight.ambient", directlightcolor*0.4f);//brighter
        modelshader.setvec3("dirlight.diffuse", directlightcolor*0.5f);
        modelshader.setvec3("dirlight.specular", directlightcolor*1.0f);
        glm::vec3 outlinecolor(outlinecolorpointer->x,outlinecolorpointer->y,outlinecolorpointer->z);
        modelshader.setvec3("outline_color", outlinecolor);

        glm::mat4 view,projection,normalmat;
        view=glm::lookAt(cameraPos,cameraPos+cameraFront,cameraUp);
        projection=glm::perspective(glm::radians(60.0f),(float)SCR_WIDTH/(float)SCR_HEIGHT,0.1f,100.0f);
        
        modelshader.setmat("perspective", projection);
        modelshader.setmat("view", view);
        modelshader.setvec3("viewpos", cameraPos);
        modelshader.setvec3("spotlight.position", cameraPos);
        modelshader.setvec3("spotlight.spot_direction", cameraFront);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_CUBE_MAP,cubemapTexture);
        modelshader.setint("cubemap", 3);
   
        glm::mat4 model=glm::mat4(1.0f);
        glm::mat4 model_outline=glm::mat4(1.0f);
        
        float angle=10.0f;
        model=glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f)); // translate it down so it's at the center of the scene
        //model matrix of nanosuit need to reduce y value
        model=glm::rotate(model,(float)glfwGetTime()*glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));
        model=glm::scale(model, glm::vec3(0.002f,0.002f,0.002f));//nanosuit need to be smaller
        
        //model_outline=glm::translate(model_outline, glm::vec3(0.0f, 0.0f, 0.0f));
        //model_outline=glm::rotate(model_outline,(float)glfwGetTime()*glm::radians(angle), glm::vec3(0.0f,1.0f,0.0f));
        //model_outline=glm::scale(model,glm::vec3(1.02f,1.02f,1.02f));
        
        modelshader.setmat("model", model);
        modelshader.setmat("model_outline", model);

        normalmat=glm::transpose(glm::inverse(model));
        modelshader.setmat("normalmat", normalmat);
        
        //add if, model_ref_shader / modelshader
        model_ref_shader.use();
        model_ref_shader.setmat("model", model);
        model_ref_shader.setmat("mode_outline", model_outline);
        model_ref_shader.setmat("view", view);
        model_ref_shader.setmat("perspective", projection);
        model_ref_shader.setmat("normalmat", normalmat);
        model_ref_shader.setvec3("cameraPos", cameraPos);
        glBindTexture(GL_TEXTURE_CUBE_MAP,cubemapTexture);
        model_ref_shader.setint("skybox", 0);
        
        model_refr_shader.use();
        model_refr_shader.setmat("model", model);
        model_refr_shader.setmat("mode_outline", model_outline);
        model_refr_shader.setmat("view", view);
        model_refr_shader.setmat("perspective", projection);
        model_refr_shader.setmat("normalmat", normalmat);
        model_refr_shader.setvec3("cameraPos", cameraPos);
        glBindTexture(GL_TEXTURE_CUBE_MAP,cubemapTexture);
        model_refr_shader.setint("skybox", 0);
        
        //draw model
        glEnable(GL_CULL_FACE);
        //glEnable(GL_MULTISAMPLE);
        if(reflect_on==false && refract_on==false)
        {
         modelshader.use();
         //for(unsigned int i=0;i<nanosuit.meshes.size();i++)
         for(unsigned int i=0;i<nanosuit.meshes.size();i++)
            {
                nanosuit.meshes[i].Draw(modelshader,outline_ornot,reflect_on);//draw complex light
            }
        }
        if(reflect_on==true)
        {
            model_ref_shader.use();

            for(unsigned int i=0;i<nanosuit.meshes.size();i++)
                {
                    nanosuit.meshes[i].Draw(model_ref_shader,outline_ornot,reflect_on);//draw simple reflection
                }
        }
        if(refract_on==true)
        {
            model_refr_shader.use();

            for(unsigned int i=0;i<nanosuit.meshes.size();i++)
                {
                    nanosuit.meshes[i].Draw(model_refr_shader,outline_ornot,refract_on);//draw simple reflection
                }
        }
        //draw z-text box
//        glEnable(GL_DEPTH_TEST);
//        glDepthFunc(GL_LESS);
//        glDisable(GL_STENCIL_TEST);
//        glDisable(GL_CULL_FACE);

        glDisable(GL_CULL_FACE);
        glm::mat4 model_box=glm::mat4(1.0f);
        model_box=glm::translate(model_box, glm::vec3(-5.0f, 0.0f, 0.0f));
        model_box=glm::scale(model_box, glm::vec3(1.0f,1.0f,1.0f));
        alphabox_shader.use();

        alphabox_shader.setmat("projection_box", projection);
        alphabox_shader.setmat("view_box", view);
        alphabox_shader.setmat("model_box", model_box);
        //glBindVertexArray(box_vao);
        //alphabox_shader.use();
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texturebox);
        //glActiveTexture(GL_TEXTURE10);
//        glBindTexture(GL_TEXTURE_CUBE_MAP,cubemapTexture);
//        modelshader.setint("cubemap", 3);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texturebox);
        glBindVertexArray(box_vao);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texturebox);
//        glBindTexture(GL_TEXTURE_2D, texturebox);
        //alphabox_shader.setint("texturebox", 0);
        
        //glBindTexture(GL_TEXTURE_2D, texturebox);
//        glBindVertexArray(box_vao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glm::mat4 model_box=glm::mat4(1.0f);
//        model_box=glm::translate(model_box, glm::vec3(-5.0f, 0.0f, 0.0f));
//        model_box=glm::scale(model_box, glm::vec3(2.0f,2.0f,2.0f));
//        alphabox_shader.use();
//
//        alphabox_shader.setmat("projection_box", projection);
//        alphabox_shader.setmat("view_box", view);
//        alphabox_shader.setmat("model_box", model_box);
//        //glBindVertexArray(box_vao);
//        //alphabox_shader.use();
////        glActiveTexture(GL_TEXTURE1);
////        glBindTexture(GL_TEXTURE_2D, texturebox);
//        //glActiveTexture(GL_TEXTURE10);
////        glBindTexture(GL_TEXTURE_CUBE_MAP,cubemapTexture);
////        modelshader.setint("cubemap", 3);
//
//        glBindVertexArray(box_vao);
////        glActiveTexture(GL_TEXTURE0);
////        glBindTexture(GL_TEXTURE_2D, texturebox);
////        glBindTexture(GL_TEXTURE_2D, texturebox);
//        //alphabox_shader.setint("texturebox", 0);
//
//        //glBindTexture(GL_TEXTURE_2D, texturebox);
////        glBindVertexArray(box_vao);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
        //glBindTexture(GL_TEXTURE_2D, 0);
        //
        
        //draw penguin
//        glm::mat4 model_penguin=glm::mat4(1.0f);
//        model_penguin=glm::translate(model_penguin, glm::vec3(-8.0f, 0.0f, 0.0f));
//        model_penguin=glm::scale(model_penguin, glm::vec3(0.005f,0.005f,0.005f));
//        bool bf=false;
//        ztest_shader.use();
//
//        ztest_shader.setmat("projection_z", projection);
//        ztest_shader.setmat("view_z", view);
//        ztest_shader.setmat("model_z", model_penguin);
//        for(unsigned int i=0;i<penguin.meshes.size();i++)
//            {
//                penguin.meshes[i].Draw(ztest_shader,bf,bf);
//            }
//
        
        
        
        
        
        //draw sphere
//        modelshader.use();
//        glm::mat4 model_sphere=glm::mat4(1.0f);
//        model_sphere=glm::translate(model_sphere, glm::vec3(-3.0f, 0.0f, 0.0f));
//        //model=glm::rotate(model,0*glm::radians(angle),glm::vec3(0.0f,1.0f,0.0f));
//        model_sphere=glm::scale(model_sphere, glm::vec3(0.05f,0.05f,0.05f));//nanosuit need to be smaller
//        modelshader.setmat("model", model_sphere);
//        normalmat=glm::transpose(glm::inverse(model_sphere));
//
//        for(unsigned int i=0;i<sphere.meshes.size();i++)
//        {
//            sphere.meshes[i].Draw(modelshader,sphere_effectoff,sphere_effectoff);//draw simple reflection
//        }
        
        //glDisable(GL_CULL_FACE);
        
        
        //draw light
        /*
        glBindVertexArray(lightVAO);
        lightshader.use();
        lightshader.setmat("view", view);
        for(unsigned int i=0;i<4;i++)
        {
        glm::mat4 model;
        model=glm::translate(model, pointLightPositions[i]);
        model=glm::scale(model, glm::vec3(0.1f));
        
        lightshader.setmat("model", model);
        lightshader.setmat("perspective", projection);
        lightshader.setvec3("pointlight_modelcolor",pointLightColors[i]);
        
        glDrawArrays(GL_TRIANGLES,0,36);
        }
        */
        
        
        //draw skybox
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glDisable(GL_STENCIL_TEST);
        //if(outline_ornot==true)glDisable(GL_STENCIL_TEST);
        //if(outline_ornot==true)glStencilMask(0x00);
        cubemapshader.use();
        cubemapshader.setmat("perspective", projection);
        glm::mat4 cubemap_view=glm::mat4(glm::mat3(view));
        //glm::mat4 cubemap_view=view;
        cubemapshader.setmat("view", cubemap_view);
        
        glBindVertexArray(cubemap_vao);
        glBindTexture(GL_TEXTURE_CUBE_MAP,cubemapTexture);
        glDrawArrays(GL_TRIANGLES,0,36);
        //glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        
    
        
        
        /*
        if(outline_ornot==true)
        {
            glEnable(GL_STENCIL_TEST);
            glStencilMask(0x00);//necessary？
            //glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
        }
         */
        
        //PASS 2: draw frame
        
        glBindFramebuffer(GL_FRAMEBUFFER,0);
        //glEnable(GL_MULTISAMPLE);
        glClearColor(0.0,0.0,1.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_STENCIL_TEST);
        //glStencilMask(0x00);
        if(sharpen_on==true)
        {
            sharpen_shader.use();
            glBindTexture(GL_TEXTURE_2D,texColorBuffer);
        }
        
        if(z_on==true)
        {
            zbuffer_shader.use();
            glBindTexture(GL_TEXTURE_2D,texDSBuffer);
        }
        if(sharpen_on==false && z_on==false)
        //else
        {
            dout_shader.use();
            glBindTexture(GL_TEXTURE_2D,texColorBuffer);
        }
        glBindVertexArray(quadVAO);
        //glBindTexture(GL_TEXTURE_2D,texColorBuffer);
        glDrawArrays(GL_TRIANGLES,0,6);
        glBindVertexArray(0);
        //glDrawArrays(GL_LINES,0,6);//线框模式
        
        
        //PASS 3: draw gui
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::Begin("Color Settings");
        ImGui::ColorEdit3("Point Light1 Color", (float*)colorpointer0);
        ImGui::ColorEdit3("Point Light2 Color", (float*)colorpointer1);
        ImGui::ColorEdit3("Point Light3 Color", (float*)colorpointer2);
        ImGui::ColorEdit3("Point Light4 Color", (float*)colorpointer3);
        ImGui::ColorEdit3("Direct Light Color", (float*)directlight_pointer);
        ImGui::ColorEdit3("Background Color", (float*)clearcolorpointer);
        ImGui::ColorEdit3("Outline Color", (float*)outlinecolorpointer);
        ImGui::Checkbox("outline", &outline_ornot);
        ImGui::Checkbox("sharpen", &sharpen_on);
        ImGui::Checkbox("show z buffer", &z_on);
        ImGui::Checkbox("reflect", &reflect_on);
        ImGui::Checkbox("refract", &refract_on);
        
        
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//        //test draw plane
//        glEnable(GL_DEPTH_TEST);
//        glEnable(GL_BLEND);
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texturebox);
//        glUseProgram(shaderProgram_01);
//               glBindVertexArray(VAO_01); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//               //glDrawArrays(GL_TRIANGLES, 0, 6);
//               glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        //test
        //test draw box
        
//        glm::mat4 model_box=glm::mat4(1.0f);
//        model_box=glm::translate(model_box, glm::vec3(-5.0f, 0.0f, 0.0f));
//        model_box=glm::scale(model_box, glm::vec3(2.0f,2.0f,2.0f));
//        alphabox_shader.use();
//
//        alphabox_shader.setmat("projection_box", projection);
//        alphabox_shader.setmat("view_box", view);
//        alphabox_shader.setmat("model_box", model_box);
//        //glBindVertexArray(box_vao);
//        //alphabox_shader.use();
////        glActiveTexture(GL_TEXTURE1);
////        glBindTexture(GL_TEXTURE_2D, texturebox);
//        //glActiveTexture(GL_TEXTURE10);
////        glBindTexture(GL_TEXTURE_CUBE_MAP,cubemapTexture);
////        modelshader.setint("cubemap", 3);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texturebox);
//        glBindVertexArray(box_vao);
////        glActiveTexture(GL_TEXTURE0);
////        glBindTexture(GL_TEXTURE_2D, texturebox);
////        glBindTexture(GL_TEXTURE_2D, texturebox);
//        //alphabox_shader.setint("texturebox", 0);
//
//        //glBindTexture(GL_TEXTURE_2D, texturebox);
////        glBindVertexArray(box_vao);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        
        
        
        
        
        
        
        
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    
    //glDeleteVertexArrays(1,&VAO);
    glDeleteVertexArrays(1,&lightVAO);
    glDeleteBuffers(1,&VBO);
    
    glfwTerminate();
    
    return 0;
}

unsigned int loadCubeMap(vector<std::string> cubemap_faces)
{
    unsigned int textureID;
    glGenTextures(1,&textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP,textureID);//the order is: right, left, top, bottom, front, back
    
    int width, height, nrChannels;
    for(unsigned int i=0; i<cubemap_faces.size(); i++)//读取cubemap的6个面
        {
            unsigned char *data=stbi_load(cubemap_faces[i].c_str(), &width, &height, &nrChannels, 0);
            if(data)
                {
                    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);//20210305 RGB2RGBA
                    stbi_image_free(data);
                }
            else{
                std::cout<<"Cubemap load error at path"<<cubemap_faces[i]<<std::endl;
                stbi_image_free(data);
            }
        }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);//mipmap
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//mipmap
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);//"GL_TEXTURE_WRAP_R", what's this??
    
    return textureID;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)//按esc退出
        glfwSetWindowShouldClose(window, true);
    float cameraspeed=2.0f*deltatime;
    
    if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS)//按w摄像机前移
        cameraPos+=cameraspeed*cameraFront;
    if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS)//按s摄像机后移
        cameraPos-=cameraspeed*cameraFront;
    
    glfwSetScrollCallback(window, scroll_callback);
    
    
    if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS)//按a摄像机左移
        cameraPos-=glm::normalize(glm::cross(cameraFront, cameraUp))*cameraspeed;
    if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS)//按d摄像机右移
        cameraPos+=glm::normalize(glm::cross(cameraFront, cameraUp))*cameraspeed;
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS)//glfwgetkey接受的是键盘按键的输入，鼠标按键不可以
        {
            //glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, mouse_callback);
            
        }
    if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)==GLFW_RELEASE)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstmouse=true;
    }
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstmouse){
        lastx=xpos;
        lasty=ypos;
        firstmouse=false;
    }
    float offsetx=xpos-lastx;
    lastx=xpos;
    float offsety=lasty-ypos;
    lasty=ypos;
    
    
    
    pitch+=offsety*sensitivity;
    yaw+=offsetx*sensitivity;
    
    if(pitch>89.0f)pitch=89.0f;
    if(pitch<-89.0f)pitch=-89.0f;
    
    glm::vec3 front;
    front.x=cos(glm::radians(yaw))*cos(glm::radians(pitch));
    front.y=sin(glm::radians(pitch));
    front.z=sin(glm::radians(yaw))*cos(glm::radians(pitch));
    cameraFront=glm::normalize(front);
}
unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT); // for this tutorial: use GL_CLAMP_TO_EDGE to prevent semi-transparent borders. Due to interpolation it takes texels from next repeat
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
