#version 330
out vec4 fragColor;
in vec4 cols;
void main() {
  fragColor = cols;
}
