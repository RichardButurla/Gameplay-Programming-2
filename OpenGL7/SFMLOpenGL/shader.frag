#version 400

uniform sampler2D f_texture;
in vec4 color;
in vec2 texel;
out vec4 fColor;
void main() {

	fColor = texture(f_texture, texel.st);
};