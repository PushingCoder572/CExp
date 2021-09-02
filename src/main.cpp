#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "STB/std_image.h"

#include "Renderer.h"

#include <GLFW/glfw3.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "Renderbuffer.h"
#include "Framebuffer.h"

using namespace std;
const char *vertexShaderSource = "../res/shaders/vertex.vs";
const char *golFragmentShaderSource = "../res/shaders/gol.fs";
const char *simpleFragmentShaderSource = "../res/shaders/simple.fs";
const char *renderFragmentShaderSource = "../res/shaders/render.fs";

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    unsigned int windowHeight = glfwGetVideoMode(glfwGetPrimaryMonitor())->height;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowHeight/2, windowHeight/2, "Game of Life", nullptr, nullptr);
    
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
      std::cout << "Error" << std::endl;
    }
    {
        float verts[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, 1.0f, 0.0f,
         1.0f,  1.0f, 1.0f, 1.0f,
        -1.0f,  1.0f, 0.0f, 1.0f
        };

        unsigned int indices[6] = {
            0, 1, 2,
            3, 2, 0
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        VertexArray va;
        VertexBuffer vb(verts, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push(GL_FLOAT, 2);
        layout.Push(GL_FLOAT, 2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        Shader gol_shader = Shader(vertexShaderSource, golFragmentShaderSource);
        gol_shader.Unbind();

        Shader simple_shader = Shader(vertexShaderSource, simpleFragmentShaderSource);
        simple_shader.Unbind();

        Shader render_shader = Shader(vertexShaderSource, renderFragmentShaderSource);
        render_shader.Unbind();

        Renderbuffer prevRbo = Renderbuffer();

        Texture prevTexture(windowHeight/2, windowHeight/2);

        Framebuffer prevFbo = Framebuffer(prevTexture.GetId(), prevRbo.GetId());

        prevFbo.Unbind();
        prevTexture.Unbind();
        prevRbo.Unbind();

        Renderbuffer nextRbo = Renderbuffer();

        Texture nextTexture(windowHeight/2, windowHeight/2);

        Framebuffer nextFbo = Framebuffer(nextTexture.GetId(), nextRbo.GetId());

        nextFbo.Unbind();
        nextTexture.Unbind();
        nextRbo.Unbind();

        vb.Unbind();
        simple_shader.Unbind();
        ib.Unbind();
        va.Unbind();

        Renderer renderer;

        double xPos, yPos = 0.0;
        bool isClick = false;
        bool isRunning = false;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            prevFbo.Bind();
            nextTexture.Bind();

            glEnable(GL_DEPTH_TEST);

            /* Render here */
            renderer.Clearback();
       
            simple_shader.Bind();
            simple_shader.Add1IntUniform("u_Color", 0);
            simple_shader.Add2FloatUniform("u_MousePos", float(xPos), float(yPos));
            simple_shader.Add1IntUniform("u_IsClick", isClick);
    
            renderer.Draw(va, ib, simple_shader);

            prevFbo.Unbind();
            nextTexture.Unbind();

            nextFbo.Bind();
            prevTexture.Bind();

            renderer.Clearback();

            if (isRunning)
            {
                gol_shader.Bind();
                gol_shader.Add1IntUniform("u_Color", 0);

                renderer.Draw(va, ib, gol_shader);
            }
            else
            {
                simple_shader.Bind();
                simple_shader.Add1IntUniform("u_Color", 0);
                simple_shader.Add2FloatUniform("u_MousePos", float(xPos), float(yPos));
                simple_shader.Add1IntUniform("u_IsClick", isClick);

                renderer.Draw(va, ib, simple_shader);
            }

            nextFbo.Unbind();
            prevTexture.Unbind();
            
            glDisable(GL_DEPTH_TEST);

            prevTexture.Bind();

            renderer.Clear();

            render_shader.Bind();
            render_shader.Add1IntUniform("u_Color", 0);

            renderer.Draw(va, ib, render_shader);

            prevTexture.Unbind();

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();

            isClick = false;
            
            int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
            if (state == GLFW_PRESS)
            {
                glfwGetCursorPos(window, &xPos, &yPos);
                isClick = true;
            }

            state = glfwGetKey(window, GLFW_KEY_SPACE);
            if (state == GLFW_PRESS)
            {
                isRunning = true;
            }
            else
            {
                isRunning = false;
            }
        }
    }
    glfwTerminate();
    return 0;
}