#version 330
layout(location = 0) in vec3 posVertex;
uniform mat4 MVP;
uniform vec4 Color;
out vec4 cols;

void main() 
{
    gl_Position = MVP * vec4(posVertex, 1.0f);
    cols = Color;
}
