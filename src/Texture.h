#pragma once

#include <string>

using namespace std;

class Texture
{
private:
   unsigned int ID;
   unsigned int Width;
   unsigned int Height;
public:
    Texture(unsigned int width, unsigned int height);
    ~Texture();

    void Bind(unsigned int slot = 0) const;
    void Unbind() const;

    inline int GetWidth() const { return Width; }
    inline int GetHeight() const { return Height; }

    inline unsigned int GetId() const { return ID; }
};
