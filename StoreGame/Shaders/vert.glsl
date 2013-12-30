#version 400

layout (location=0) in vec4 position;
layout (location=1) in vec4 color;

uniform float loopDuration;
uniform float time;

smooth out vec4 vertColor;

void main()
{
	float timeScale = 3.14159f * 2.0f / loopDuration;

	float curTime = mod(time, loopDuration);
	vec4 totalOffset = vec4(
		cos(curTime * timeScale) * 0.5f,
		sin(curTime * timeScale) * 0.5f,
		0.0f,
		0.0f
	);

	gl_Position = position + totalOffset;
	vertColor = color;
}