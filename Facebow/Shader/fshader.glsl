//#version 330
//in vec4 cols;
//out vec4 fragColor;
//void main()
//{
//  fragColor = cols;
//};


#version 330
in vec4 realPos;
in vec4 norms;
in vec4 cols;
uniform vec3 lightPos;
out vec4 fragColor;
uniform sampler2D imgTexture;
void main() {
      vec3 pos = realPos.xyz / realPos.w;
      vec3 lightSourceDir = normalize(pos - lightPos);
      vec3 norm3D = normalize(norms.xyz / norms.w);
      float diffuse = max(dot(lightSourceDir, norm3D), 0);
      float lightDeg = diffuse * 0.9 +0.1;
      fragColor = cols * lightDeg;
}
