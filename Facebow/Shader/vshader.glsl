//#version 330
//layout(location = 0) in vec3 posVertex;
//layout(location = 1) in vec3 normVertex;

//uniform mat4 MVP;
//out vec4 cols;

//void main()
//{
//  gl_Position = MVP * vec4(posVertex, 1.0f);
//  cols = vec4(1.0f, 0.5f, 0.5f, 1.0f);
//}


#version 330
layout(location = 0) in vec3 posVertex;
layout(location = 1) in vec3 normVertex;

uniform mat4 vpMat;
uniform mat4 modelMat;

out vec4 realPos;
out vec4 norms;
out vec4 cols;

void main() {
    realPos = modelMat * vec4(posVertex, 1.0f);
    norms = modelMat * vec4(normVertex, 1.0f);
    gl_Position = vpMat * realPos;
    cols = vec4(0.5f, 0.5f, 0.5f, 1.0f);
}
