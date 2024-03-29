#version 120

uniform vec4 iMouse;
uniform vec3 iResolution;
uniform float iGlobalTime;

uniform float faceEyeLeft;
uniform float faceEyeRight;
uniform float faceEyebrowLeft;
uniform float faceEyebrowRight;


void main()
{

//    vec3 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
//    pos.x = sin(iGlobalTime) * 5.0 + position.x;
//    gl_Position = pos;
    vec4 position = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
    position.x = sin(iGlobalTime*position.x/10.0) * faceEyebrowLeft *10.0 + position.x;
    position.y = cos(iGlobalTime*position.y/10.0) * faceEyebrowRight * 10.0 + position.y;

    gl_Position = position;
}