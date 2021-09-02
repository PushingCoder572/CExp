#pragma once

#include <vector>
#include <iostream>
#include "Renderer.h"

using namespace std;

struct VertexBufferElement
{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    }
};

class VertexBufferLayout
{
private:
    std::vector<VertexBufferElement> Elements;
    unsigned int Stride;
public:
    VertexBufferLayout()
        : Stride(0) {}
    
    void Push(GLuint type, unsigned int count, bool normalize = false)
    {
        struct VertexBufferElement p1 = {type, count, normalize};
        Elements.push_back(p1);
        Stride += count * VertexBufferElement::GetSizeOfType(type);
    }

    inline const std::vector<VertexBufferElement> GetElements() const { return Elements; }
    inline unsigned int GetStride() const { return Stride; }
};