#version 450

layout(location = 0) in vec3 vColor;
layout(location = 1) in vec2 vUV;
layout(location = 2) in float vHeight;

layout(location = 0) out vec4 outColor;

void main()
{
    float minH = 130.0;
    float maxH = 160.0;

    float t = (vHeight - minH) / (maxH - minH);
    t = clamp(t, 0.0, 1.0);

    // grayscale color
    vec3 gray = vec3(t);
    outColor = vec4(gray, 1.0);
}
