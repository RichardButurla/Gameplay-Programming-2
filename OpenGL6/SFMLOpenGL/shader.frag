#version 400

in vec4 color;
out vec4 fColor;
void main() 
{
	fColor = color + vec4(0.0f, 0.0f, 0.5f, 0.5f);
};