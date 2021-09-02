#pragma once

#include <string>

class Shader
{
private:
   unsigned int RenderId;
public:
    Shader(const char* VertexPath, const char* FragPath);
    ~Shader();

    void Add4FloatUniform(const char* name, float v1, float v2, float v3, float v4);
    void Add1IntUniform(const char* name, int v1);
    void Add2FloatUniform(const char* name, float v1, float v2);

    void Bind() const;
    void Unbind() const;
};
