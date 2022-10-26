#version 330 core
out vec4 FragColor;
uniform sampler2D tex;
in vec2 pos;

int setCol(vec4);


uniform vec4 colors[16];



void main()
{


    vec2 uPos;
    vec2 dPos;
    vec2 lPos;
    vec2 rPos;

    float d = 1.0 / 1000.0;

    if (pos.x - d < 0.0)
    {
        lPos = vec2(1.0, pos.y);
    }
    else
    {
        lPos = vec2(pos.x - d, pos.y);
    }
    if (pos.x + d > 1.0)
    {
        rPos = vec2(0.0, pos.y);
    }
    else
    {
        rPos = vec2(pos.x + d, pos.y);
    }
    if (pos.y - d < 0.0)
    {
        uPos = vec2(pos.x, 1.0);
    }
    else
    {
        uPos = vec2(pos.x, pos.y - d);
    }
    if (pos.y + d > 1.0)
    {
        dPos = vec2(pos.x, 0.0);
    }
    else
    {
        dPos = vec2(pos.x, pos.y + d);
    }

    vec4 uC = texture(tex,uPos);
    vec4 dC = texture(tex,dPos);
    vec4 lC = texture(tex,lPos);
    vec4 rC = texture(tex,rPos);
    vec4 cC = texture(tex,pos);




    int uN = setCol(uC);
    int dN = setCol(dC);
    int lN = setCol(lC);
    int rN = setCol(rC);
    int cN = setCol(cC);


    
    if (((uN - cN == 1) || (uN - cN == -15)) || ((dN - cN == 1) || (dN - cN == -15)) || ((lN - cN == 1) || (lN - cN == -15)) || ((rN - cN == 1) || (rN - cN == -15)))
    {
        cN = (cN + 1)%16;
    }


    vec4 a = colors[cN];

    FragColor = vec4(float(a.r)/255, float(a.g)/255, float(a.b)/255, 1.0);     




} 



int setCol(vec4 V)
{
    if (V.r == 0.0 && V.g == 0.0 && V.b == 0.0)
    {
        return 0;
    }
    if (V.r == 15.0/255 && V.g == 15.0/255 && V.b == 15.0/255)
    {
        return 1;
    }
    if (V.r == 0.0 && V.g == 0.0 && V.b == 1.0)
    {
        return 2;
    }
    if (V.r == 15.0/255 && V.g == 15.0/255 && V.b == 1.0)
    {
        return 3;
    }
    if (V.r == 0.0 && V.g == 1.0 && V.b == 0.0)
    {
        return 4;
    }
    if (V.r == 15.0/255 && V.g == 1.0 && V.b == 15.0/255)
    {
        return 5;
    }
    if (V.r == 0.0 && V.g == 1.0 && V.b == 1.0)
    {
        return 6;
    }
    if (V.r == 15.0/255 && V.g == 1.0 && V.b == 1.0)
    {
        return 7;
    }
    if (V.r == 1.0 && V.g == 0.0 && V.b == 0.0)
    {
        return 8;
    }
    if (V.r == 1.0 && V.g == 15.0/255 && V.b == 15.0/255)
    {
        return 9;
    }
    if (V.r == 1.0 && V.g == 0.0 && V.b == 1.0)
    {
        return 10;
    }
    if (V.r == 1.0 && V.g == 15.0/255 && V.b == 1.0)
    {
        return 11;
    }
    if (V.r == 1.0 && V.g == 1.0 && V.b == 0.0)
    {
        return 12;
    }
    if (V.r == 1.0 && V.g == 1.0 && V.b == 15.0/255)
    {
        return 13;
    }
    if (V.r == 1.0 && V.g == 1.0 && V.b == 1.0)
    {
        return 14;
    }
    if (V.r == 1.0 && V.g == 1.0 && V.b == 240.0/255)
    {
        return 15;
    }

}
