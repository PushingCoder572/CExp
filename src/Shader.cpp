#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <vector>

static std::string readFile(const char *filePath)
{
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open())
    {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}


Shader::Shader(const char* VertexPath, const char* FragPath)
{
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    std::string vertShaderStr = readFile(VertexPath);
    std::string fragShaderStr = readFile(FragPath);
    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLength;

    std::cout << "Compliling vertex shader." << std::endl;
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &vertShaderError[0]);
    std::cout << &vertShaderError[0] << std::endl;

    std::cout << "Compiling fragment shader." << std::endl;
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);
    
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    std::cout << &fragShaderError[0] << std::endl;

    std::cout << "Linking program" << std::endl;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError((logLength > 1) ? logLength : 1);
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    RenderId = program;
}

Shader::~Shader()
{
    glDeleteProgram(RenderId);
}

void Shader::Add4FloatUniform(const char* name, float v1, float v2, float v3, float v4)
{
    Bind();
    int location = glGetUniformLocation(RenderId, name);
    glUniform4f(location, v1, v2, v3, v4);
}

void Shader::Add1IntUniform(const char* name, int v1)
{
    Bind();
    int location = glGetUniformLocation(RenderId, name);
    glUniform1i(location, v1);
}

void Shader::Add2FloatUniform(const char* name, float v1, float v2)
{
    Bind();
    int location = glGetUniformLocation(RenderId, name);
    glUniform2f(location, v1, v2);
}

void Shader::Bind() const
{
    glUseProgram(RenderId);
}

void Shader::Unbind() const
{
    glUseProgram(0);
}