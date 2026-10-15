#version 450

layout(location = 0) out vec4 outColor;

layout(location = 0) in vec4 fragColor;
layout(location = 1) in vec2 fragTexCoord;

layout(set = 1, binding = 0) uniform sampler2D glyphAtlas;

void main()
{
    float coverage = texture(glyphAtlas, fragTexCoord).r;
    outColor = vec4(fragColor.rgb, fragColor.a * coverage);
}
