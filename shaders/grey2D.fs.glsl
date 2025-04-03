#version 330 core

in vec3 vFragColor;

out vec3 fFragColor;

void main() {
  float grey = (vFragColor[0] + vFragColor[1] + vFragColor[2]) / 3.0;
  fFragColor = vec3(grey,grey,grey);
};