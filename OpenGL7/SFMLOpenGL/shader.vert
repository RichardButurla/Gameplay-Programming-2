#version 400

in vec4 sv_position;
in vec4 sv_color;
in vec2 sv_texel;
out vec4 color;
out vec2 texel;
void main() {
	color = sv_color;
	texel = sv_texel;
	gl_Position = sv_position;
};