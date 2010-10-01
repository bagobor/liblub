#version 330 core

precision highp float;

in vec4 positionView;
in vec3 normalView;

out vec4 finalColor;

uniform vec4 lightPositionView;

uniform vec4 lightColor;

//ambient
uniform vec4 ambientSceneColor;
//specular
uniform float shininess;
uniform vec4 specularMaterialColor;

#ifdef useDiffuseTexture
in vec2 uv;
uniform sampler2D diffuseTexture;
#else
uniform vec4 diffuseMaterialColor;
#endif

//spot
uniform float spotInnerAngle;
uniform float spotOuterAngle;
uniform vec3 spotDirectionView;

//attenuation
uniform float constantAttenuation;
uniform float linearAttenuation;
uniform float quadraticAttenuation;


vec4 diffuseColor(float lambertTerm){

	return	
#ifdef useDiffuseTexture
		texture(diffuseTexture, uv) *
#else
		diffuseMaterialColor *
#endif
			lightColor * 
			lambertTerm;
}

vec4 specularColor(float specular){

	return	specularMaterialColor * 
			lightColor * 
			specular;	
}

void main(){ 

	vec4 lightDirection = lightPositionView - positionView;

	float d = length(lightDirection);
		
	float att = 1.0 / ( 
			constantAttenuation + 
			(linearAttenuation * d) + 
			(quadraticAttenuation * d * d) 
	);

	//ambient
	finalColor = ambientSceneColor;
								
	vec3 L = normalize(lightDirection.xyz);	

	//Spot	
	float spotCurAngle = dot(-L, spotDirectionView);
	float spotAngleDiff =  spotOuterAngle - spotInnerAngle;
	float spot = clamp((spotCurAngle - spotOuterAngle) / spotAngleDiff, 0.0, 1.0);

	vec3 N = normalize(normalView);
	
	//float lambertTerm = dot(N,L);

	float lambertTerm = max( dot(N,L), 0.0);

	if(lambertTerm > 0.0)
	{
		//diffuse
		finalColor += diffuseColor(lambertTerm) * att * spot;
		
		//specular
		vec3 E = normalize(-positionView.xyz);
		vec3 R = reflect(-L, N);

		float specular = pow( max(dot(R, E), 0.0), shininess );
		finalColor += specularColor(specular) * att * spot;
	}
			
} 

