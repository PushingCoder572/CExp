#pragma once

class Renderbuffer
{
private:
    unsigned int RenderId;
public:
    Renderbuffer(unsigned int Width, unsigned int Height);
    ~Renderbuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetId() const { return RenderId; }
};