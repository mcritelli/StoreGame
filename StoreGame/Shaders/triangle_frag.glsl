#version 400

smooth in vec4 vertColor;

uniform float fragLoopDuration;
uniform float fragTime;

const vec4 firstColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
const vec4 secondColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);

out vec4 outColor;

void main()
{
	//float lerpValue = gl_FragCoord.y / 600.0f;

	//outColor = mix(
		//vec4(1.0f, 1.0f, 1.0f, 1.0f),
		//vec4(0.2f, 0.2f, 0.2f, 1.0f),
		//lerpValue
	//);
	
	float curTime = mod(fragTime, fragLoopDuration);
	float curLerp = curTime / fragLoopDuration;

	//outColor = vertColor;
	outColor = mix(vec4(vertColor.g, vertColor.b, vertColor.r, vertColor.a), vertColor, curLerp);
    //outColor = vec4(1.0, 1.0, 1.0, 1.0);
}