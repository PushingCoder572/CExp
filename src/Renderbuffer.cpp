#include "Renderer.h"
#include "Renderbuffer.h"

#include <iostream>

Renderbuffer::Renderbuffer(unsigned int Width, unsigned Height)
{
    glGenRenderbuffers(1, &RenderId);
    glBindRenderbuffer(GL_RENDERBUFFER, RenderId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, Width, Height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Renderbuffer::~Renderbuffer()
{
    glDeleteRenderbuffers(1, &RenderId);
}

void Renderbuffer::Bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, RenderId);
}

void Renderbuffer::Unbind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}