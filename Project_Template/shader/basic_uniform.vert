#version 460


layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 position;
out vec3 normal;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main() { 

 normal = normalize( NormalMatrix * VertexNormal);

 position = (ModelViewMatrix * vec4(VertexPosition,1.0)).xyz;

 gl_Position = MVP * vec4(VertexPosition,1.0);

}
