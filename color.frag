#version 450

layout(location = 0) in vec3 vColor;

layout(location = 0) out vec4 fragColor;

layout(location = 2) in float vHeight;

void main()
{
    //fragColor = vec4(vColor, 1.0);

    float minH = -10.0;
    float maxH =  20.0;

    float t = (vHeight - minH) / (maxH - maxH);
    t = clamp(t, 0.0, 1.0);

    vec3 grayscale = vec3(t);
    fragColor = vec4(grayscale, 1.0);
}
