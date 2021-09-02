#version 330 core
layout (location=0) out vec4 FragColor;

in vec2 v_TexCoord;

uniform sampler2D u_Color;

int edgeCheck(const float offset)
{
    int posSum = 0;

    //Left
    if (v_TexCoord.x < offset)
    {
        posSum += 2;

        //Bottom
        if (v_TexCoord.y < offset)
        {
            posSum += 3;
        }
        //Top
        else if (v_TexCoord.y > 1 - offset)
        {
            posSum += 1;
        }
    }
    //Right
    else if (v_TexCoord.x > 1 - offset)
    {
        posSum += 4;

        //Bottom
        if (v_TexCoord.y < offset)
        {
            posSum += 3;
        }
        //Top
        else if (v_TexCoord.y > 1 - offset)
        {
            posSum += 1;
        }
    }
    else
    {
        //Bottom
        if (v_TexCoord.y < offset)
        {
            posSum += 3;
        }
        //Top
        else if (v_TexCoord.y > 1 - offset)
        {
            posSum += 1;
        }
    }

    return posSum;
}

int nCheck(const float offset, const int pos)
{
    float sum = 0;

    if (pos == 0)
    {
        sum += texture(u_Color, v_TexCoord + vec2(offset,   offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(offset,        0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(offset,  -offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(0,        offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(0,       -offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset,  offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset,       0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset, -offset)).r;
    }
    else if (pos == 1)
    {
        sum += texture(u_Color, v_TexCoord + vec2(offset,        0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(offset,  -offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(0,       -offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset,       0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset, -offset)).r;
    }
    else if (pos == 2)
    {
        sum += texture(u_Color, v_TexCoord + vec2(offset,   offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(offset,        0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(offset,  -offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(0,        offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(0,       -offset)).r;
    }
    else if (pos == 3)
    {
        sum += texture(u_Color, v_TexCoord + vec2(offset,        0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(offset,  -offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(0,       -offset)).r;
    }
    else if (pos == 4)
    {
        sum += texture(u_Color, v_TexCoord + vec2(0,        offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(0,       -offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset,  offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset,       0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset, -offset)).r;
    }
    else if (pos == 5)
    {
        sum += texture(u_Color, v_TexCoord + vec2(0,       -offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset,       0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset, -offset)).r;
    }
    else if (pos == 6)
    {
        sum += texture(u_Color, v_TexCoord + vec2(offset,   offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(offset,        0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(0,        offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset,  offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(-offset,       0)).r;
    }
    else if (pos == 8)
    {
        sum += texture(u_Color, v_TexCoord + vec2(offset,   offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(offset,        0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(0,        offset)).r;
    }
    else if (pos == 10)
    {
        sum += texture(u_Color, v_TexCoord + vec2(offset,        0)).r;
        sum += texture(u_Color, v_TexCoord + vec2(offset,  -offset)).r;
        sum += texture(u_Color, v_TexCoord + vec2(0,       -offset)).r;
    }

    return int(sum);

}

void main()
{
    const float offset = 1.0 / 720.0;
    
    vec4 live = vec4(1.0, 0.0, 1.0, 1.0);
    vec4 dead = vec4(0.0, 0.0, 0.0, 1.0);
    
    int n_check = nCheck(offset, edgeCheck(offset));

    bool alive = (texture(u_Color, v_TexCoord).r == 1.0);

    if (alive)
    {
        if (n_check == 2 || n_check == 3)
        {
            FragColor = live;
        }
        else
        {
            FragColor = dead;
        }
    }
    else
    {
        if (n_check == 3)
        {
            FragColor = live;
        }
        else
        {
            FragColor = dead;
        }
    }

}