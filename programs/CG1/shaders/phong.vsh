varying vec3 normal, lightDir, options;


void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
    lightDir = normalize(vec3(gl_LightSource[0].position));
    normal = normalize(gl_NormalMatrix * gl_Normal);

    gl_Position = ftransform();
}
