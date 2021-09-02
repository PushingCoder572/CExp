#pragma once

class Renderbuffer
{
private:
    unsigned int RenderId;
public:
    Renderbuffer();
    ~Renderbuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetId() const { return RenderId; }
};