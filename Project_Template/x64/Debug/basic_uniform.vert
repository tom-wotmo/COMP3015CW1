#version 460


layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;
layout (location = 2) in vec2 VertexTexCoord;

out vec3 position;
out vec3 normal;
out vec2 TexCoord;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main() 
{ 

 normal = normalize( NormalMatrix * VertexNormal);

 position = (ModelViewMatrix * vec4(VertexPosition,1.0)).xyz;

 TexCoord = VertexTexCoord;

 gl_Position = MVP * vec4(VertexPosition,1.0);

}
