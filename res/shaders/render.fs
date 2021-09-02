#version 330 core
layout (location=0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_Color;

void main()
{
   if (texture(u_Color, v_TexCoord).r == 1.0)
   {
       FragColor = vec4(v_TexCoord.x, v_TexCoord.y, 0.0, 1.0);
   }
}