#ifndef TOON_SHADER_H
#define TOON_SHADER_H

#include <QString>

const QString kToonShaderVert =
    "varying vec3 normal, lightDir, options; \n"
    "void main() \n"
    "{ \n"
        "lightDir = normalize(vec3(gl_LightSource[0].position)); \n"
        "normal = normalize(gl_NormalMatrix * gl_Normal); \n"

        "gl_Position = ftransform(); \n"
    "}";

const QString kToonShaderFrag =
    "varying vec3 normal, lightDir; \n"
    "uniform sampler2D color_texture; \n"
    "void main() \n"
    "{ \n"
        "float intensity; \n"
        "vec3 n; \n"
        "vec4 color; \n"

        "n = normalize(normal); \n"
        "intensity = max(dot(lightDir,n),0.0); \n"

        "if (intensity > 0.98) \n"
            "color = vec4(1.0,1.0,1.0,1.0); \n"
        "else if (intensity > 0.5) \n"
            "color = vec4(0.6,0.6,0.6,1.0); \n"
        "else if (intensity > 0.25) \n"
            "color = vec4(0.3,0.3,0.3,1.0); \n"
        "else \n"
            "color = vec4(0.1,0.1,0.1,1.0); \n"
        "gl_FragColor = color; \n"
    "}";

#endif // TOON_SHADER_H
