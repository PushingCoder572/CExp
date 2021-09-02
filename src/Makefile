all: compile link

compile:
	g++ -I ../dep/include -I ** -c main.cpp Texture.cpp VertexArray.cpp IndexBuffer.cpp VertexBuffer.cpp Renderer.cpp Shader.cpp Framebuffer.cpp Renderbuffer.cpp
link:
	g++ main.o Texture.o VertexArray.o IndexBuffer.o VertexBuffer.o Renderer.o Shader.o Framebuffer.o Renderbuffer.o -o app -L ../dep/lib -l glew32s -l glfw3 -l opengl32 -l gdi32 -l user32 -l kernel32