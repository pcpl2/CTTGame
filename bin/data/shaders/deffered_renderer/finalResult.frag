#version 330 core

uniform sampler2D diffuseTexture; 
uniform sampler2D normalTexture;
uniform sampler2D depthTexture;

in vec2 vUV;

uniform mat4 unProjectMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 color;

vec3 getWorldPosition()
{
    float z = texture(depthTexture, vUV).r* 2.0 - 1.0;
    vec4 screenPosition = vec4(vUV * 2.0 - 1.0, z, 1.0);
    screenPosition = unProjectMatrix * screenPosition;

    return (screenPosition.xyz / screenPosition.w);
}

void main(void)
{	
	vec3 ambient = vec3(1, 1, 1);
	int numLights = 0;

	// Base color of texture
	color = texture2D(diffuseTexture, vUV);

	// Get world position from depth buffer
	vec3 vecPosition = getWorldPosition();
	vec3 vecNormal = normalize(texture2D(normalTexture, vUV).xyz);

	//color = vec4(1,1,1,1);
	//color = vec4(vecNormal, 1);

	vec3 lighting;

	float power = 1.f;	
	float size = 1000.0f;
	vec3 lightColor = vec3(0.8, 0.8, 0.8);
	vec3 lightPosition = vec3(20,100,0);

	float mp = 0;
	float _dot = dot(normalize(lightPosition-vecPosition), vecNormal);
	if(_dot > 0)
	{
		mp = clamp(1 - distance(lightPosition, vecPosition) / size, 0, 1) * _dot;
	}	
	else
	{
		mp = 0;
	}

	if(mp > 0)	
		numLights++;
	lighting += vec3(lightColor * (power * mp));

	power = 5.f;
	size = 20.0f;
	lightColor = vec3(0.5,0.2,0);
	lightPosition = vec3(10,2,10);
	
	_dot = dot(normalize(lightPosition-vecPosition), vecNormal);
	if(_dot > 0)
	{
		mp = clamp(1 - distance(lightPosition, vecPosition) / size, 0, 1) * _dot;
	}	
	else
	{
		mp = 0;
	}

	if(mp > 0)	
		numLights++;
	lighting += vec3(lightColor * (power * mp));

	/*lightColor = vec3(0.3,0.0,0.5);
	lightPosition = vec3(10,1,0);
	
	_dot = dot(normalize(lightPosition-vecPosition), vecNormal);
	if(_dot > 0)
	{
		mp = clamp(1 - distance(lightPosition, vecPosition) / 8, 0, 1) * _dot;
	}	
	else
	{
		mp = 0;
	}


	if(mp > 0)	
		numLights++;
	color *= vec4(lightColor * (power * mp), 1);

	lightColor = vec3(0.01,0.03,0.08);
	lightPosition = vec3(0,1,10);
	
	_dot = dot(normalize(lightPosition-vecPosition), vecNormal);
	if(_dot > 0)
	{
		mp = clamp(1 - distance(lightPosition, vecPosition) / 8, 0, 1) * _dot;
	}	
	else
	{
		mp = 0;
	}


	if(mp > 0)	
		numLights++;
	color *= vec4(lightColor * (power * mp), 1);*/

	color *= vec4(lighting /* ambient*/, 1);
//	color /= 2;

	/*if(numLights > 0)
		color /= numLights;*/
}