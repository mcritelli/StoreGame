#version 400

layout(location=0) in vec4 position;
layout(location=1) in vec4 color;

smooth out vec4 theColor;

uniform mat4 modelMatrix;
uniform mat4 perspectiveMatrix;

void main()
{
	//vec4 cameraPos = position + vec4(offset.x, offset.y, offset.z, 0.0);
	vec4 cameraPos = modelMatrix * position;

	gl_Position = perspectiveMatrix * cameraPos;
	theColor = color;
}