#version 460

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

uniform struct LightInfo
{
vec4 Position;
vec3 Ld;

}Light;
uniform struct MaterialInfo
{
vec3 Kd;

}Material;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main()
{
vec3 n = normalize(NormalMatrix * VertexNormal);

vec4 pos = ModelViewMatrix * vec4(VertexPosition, 1.0);

vec3 s = normalize(vec3(Light.Position - pos));

float sDotN = max(dot(s,n), 0.0 );

vec3 diffuse = Light.Ld * Material.Kd * sDotN;

LightIntensity = diffuse;

gl_Position = MVP * vec4(VertexPosition, 1.0);
 
}

