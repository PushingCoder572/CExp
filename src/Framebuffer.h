#pragma once

class Framebuffer
{
private:
    unsigned int RenderId;
public:
    Framebuffer(const unsigned int buffertexture, const unsigned int renderbuffer);
    ~Framebuffer();

    void Bind() const;
    void Unbind() const;
};