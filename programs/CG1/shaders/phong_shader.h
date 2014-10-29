#ifndef PHONG_SHADER_H
#define PHONG_SHADER_H

#include <QString>

const QString kPhongShaderVert =
    "varying vec3 N; \n"
    "varying vec3 v; \n"
    "varying vec4 t; \n"
    "void main(void) \n"
    "{ \n"
    "  t = gl_MultiTexCoord0; \n"
    "  v = vec3(gl_ModelViewMatrix * gl_Vertex); \n"
    "  N = normalize(gl_NormalMatrix * gl_Normal); \n"
    "  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; \n"
    "} \n";


const QString kPhongShaderFrag =
    "varying vec3 N; \n"
    "varying vec3 v; \n"
    "varying vec4 t; \n"
    "uniform sampler2D color_texture; \n"
    "void main (void) \n"
    "{ \n"
    "  vec3 L = normalize(gl_LightSource[0].position.xyz - v); \n"
    "  vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0) \n"
    "  vec3 R = normalize(-reflect(L,N)); \n"
    " \n"
    "  //calculate Ambient Term: \n"
    "  vec4 Iamb = gl_FrontLightProduct[0].ambient; \n"
    " \n"
    "  //calculate Diffuse Term: \n"
    "  vec4 Idiff = gl_FrontLightProduct[0].diffuse * max(dot(N,L), 0.0); \n"
    "  Idiff = clamp(Idiff, 0.0, 1.0); \n"
    " \n"
    "  // calculate Specular Term: \n"
    "  vec4 Ispec = gl_FrontLightProduct[0].specular \n"
    "               * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess); \n"
    "  Ispec = clamp(Ispec, 0.0, 1.0); \n"
    "  // write Total Color: \n"
    "  gl_FragColor = ( gl_FrontLightModelProduct.sceneColor + Iamb + Idiff + Ispec ) * texture2D(color_texture,t.st); \n"
    "} \n";

#endif // PHONG_SHADER_H
