#version 330 core

uniform sampler2D diffuse;

in vec4 vColor;
in vec2 vUV;
in vec3 vNormal;

layout(location = 0) out vec3 outDiffuse;
layout(location = 1) out vec3 outNormal;
layout(location = 2) out float outDepth;

// Simple deffered fragment shader
void main(void)
{	
	outDiffuse = vColor.rgb * texture2D(diffuse, vUV).rgb;
	outNormal = vNormal;
	outDepth = gl_FragCoord.z;
}