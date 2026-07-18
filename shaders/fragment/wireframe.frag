#version 450

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec3 fragColor;

void main()
{
    outColor = vec4(vec3(1.0, 0.7, 0.3), 1.0);
}
