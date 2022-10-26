#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 tPos;
out vec2 pos;
void main()
{
    pos = tPos;
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}