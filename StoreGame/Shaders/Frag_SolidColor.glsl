#version 400

uniform vec4 inColor;

out vec4 outColor;

void main()
{
	float lerp = gl_FragCoord.y / 500.0f;
	outColor = mix(inColor, vec4(inColor.g, inColor.b, inColor.r, inColor.a), lerp);

	//outColor = inColor;
}