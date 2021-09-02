#include "Framebuffer.h"
#include "Renderer.h"

#include <iostream>

Framebuffer::Framebuffer(const unsigned int buffertexture, const unsigned int renderbuffer)
{
    glGenFramebuffers(1, &RenderId);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, RenderId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffertexture, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &RenderId);
}

void Framebuffer::Bind() const 
{
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, RenderId);
}

void Framebuffer::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
