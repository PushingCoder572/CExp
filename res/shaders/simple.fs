#version 330 core
layout (location=0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_Color;
uniform vec2 u_MousePos;
uniform bool u_IsClick;
uniform vec2 u_screenSize;

void main()
{
   if (u_IsClick)
   {
      if (u_MousePos.x == int(v_TexCoord.x * u_screenSize.x) && u_MousePos.y == int((1 - v_TexCoord.y) * u_screenSize.y))
      {
         FragColor = vec4(1.0, 0.0, 0.0, 1.0);
      }
      else
      {
         FragColor = texture(u_Color, v_TexCoord);
      }
   }
   else
   {
      FragColor = texture(u_Color, v_TexCoord);
   }
}