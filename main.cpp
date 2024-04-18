#include <cstdlib>
#include <imgui.h>
#define GLAD_GL_IMPLEMENTATION
#include<glad/glad.h>
#include <iostream>
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


#include "linmath.h"

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <array>





class myInterface
{
public:
    myInterface(GLFWwindow* w) :m_window(w)
    {
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void InitFrameImGUI()
    {
        //Start a new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Add your GUI elements here
        ImGui::Text("Color");
        static float col[3] = { 25.,0.,9. };
        ImGui::ColorEdit3("Color Picker", col);
        // color[0] = col[0];
        // color[1] = col[1];
        // color[2] = col[2];
        std::move(std::begin(col), std::end(col), m_color.begin());
        ImGui::SliderFloat3("Rotation", rotation, -180.0f, 180.0f);
        ImGui::SliderFloat("Scale", scale, 0.1f, 10.f);

    }

    void Show()
    {
        // // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    
    std::array<float, 3>  GetColor() const
    {
        return m_color;
    }

    float GetRotation(int n)
    {
        return rotation[n];
    }

    float GetScale()
    {
        return scale[0];
    }

    virtual ~myInterface()
    {
        // Cleanup
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

private:
    GLFWwindow* m_window;
    std::array<float, 3> m_color;
    float rotation[3] = { 0.0f, 0.0f, 0.0f };
    float scale[1] = { 1.2f };
};

typedef struct Vertex
{
    float pos[3] = { 0.0f, 0.0f, 0.0f };
    float col[3] = { 0.0f, 0.0f, 0.0f };
} Vertex;




float x = 0.0f;
Vertex vertices[] =
{
    { { 0.5f , -0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f } }, //основание
    { { 0.5f , -0.5f, -0.5f }, { 0.f, 1.f, 0.f } },
    { { 0.5f , -0.5f, -0.5f }, { 0.f, 0.f, 1.f } },
    { { -0.5f , -0.5f, -0.5f }, { 0.f, 0.f, 1.f } },
    { { -0.5f  , -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f } },
    { { -0.5f , -0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f } },
    { { -0.5f , -0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.5f , -0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.5f , -0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f } },//вершина
    { { 0.0f, 0.5f, 0.0f } , { 0.0f, 0.0f, 0.0f } },
    { { 0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.5f, 0.0f } , { 0.0f, 0.0f, 0.0f } },
    { { -0.5f, -0.5f, 0.5f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.5f, 0.0f } , { 0.0f, 0.0f, 0.0f } },
    { { -0.5f, -0.5f, -0.5f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.5f, 0.0f } , { 0.0f, 0.0f, 0.0f } }
};


static const char* vertex_shader_text =
"#version 330\n"
"uniform mat4 MVP;\n"
"in vec3 vCol;\n"
"in vec3 vPos;\n"
"out vec3 color;\n"
"void main()\n"
"{\n"

"    gl_Position = MVP * vec4(vPos.x, vPos.y, vPos.z, 1.0);\n"
"    color = vCol;\n"

"}\n";

static const char* fragment_shader_text =
"#version 330\n"
//    "in vec3 color;\n"
"uniform float red;\n"
"uniform float green;\n"
"uniform float blue;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(red, green, blue, 1.0);\n"
"}\n";

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}



float x_1 = 0.0f, y_1 = 0.0f, z_1 = 0.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        x_1 += 0.1f;
    else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        x_1 -= 0.1f;
    else if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        y_1 += 0.1f;
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        y_1 -= 0.1f;
}

int main(void)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    GLFWwindow* window = glfwCreateWindow(1920, 1080, "Dashapupu", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwMakeContextCurrent(window);

    //Initialize ImGui
    myInterface obj(window);


    gladLoadGL();
    glfwSwapInterval(1);

    // NOTE: OpenGL error checks have been omitted for brevity

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);


    const GLint mvp_location = glGetUniformLocation(program, "MVP");
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");

    GLuint vertex_array;
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), (void*)offsetof(Vertex, col));

    while (!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        const float ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        mat4x4 m, p, s, t, mvp;
        mat4x4_identity(m);
        mat4x4_identity(p);
        mat4x4_identity(s);
        mat4x4_identity(t);
        mat4x4_rotate_X(m, m, obj.GetRotation(0) / 57.2958);
        mat4x4_rotate_Y(m, m, obj.GetRotation(1) / 57.2958);
        mat4x4_rotate_Z(m, m, obj.GetRotation(2) / 57.2958);
        mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);

        s[0][0] = 1 * obj.GetScale();
        s[1][1] = 1 * obj.GetScale();
        s[2][2] = 1 * obj.GetScale();

        mat4x4_translate(t, x_1, y_1, z_1);

        mat4x4_mul(mvp, p, m);
        mat4x4_mul(mvp, mvp, s);
        mat4x4_mul(mvp, mvp, t);

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*)&mvp);
        glBindVertexArray(vertex_array);
        glDrawArrays(GL_LINES, 0, 16);

        //in while
        obj.InitFrameImGUI();
        obj.Show();
        //to send a data to fragment shader
        glUniform1f(glGetUniformLocation(program, "red"), obj.GetColor()[0]);
        glUniform1f(glGetUniformLocation(program, "green"), obj.GetColor()[1]);
        glUniform1f(glGetUniformLocation(program, "blue"), obj.GetColor()[2]);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}