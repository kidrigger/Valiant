#version 330 core
struct Material {
	sampler2D texture_diffuse0;
	sampler2D texture_specular0;
	sampler2D texture_normal0;
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
	sampler2D texture_normal1;
	sampler2D texture_diffuse2;
	sampler2D texture_specular2;
	sampler2D texture_normal2;
	sampler2D texture_diffuse3;
	sampler2D texture_specular3;
	sampler2D texture_normal3;
	float shinyness;
};

struct DirLight {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	vec3 direction;
};

struct PointLight {
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
	vec3 position;
	float linear;
	float quadratic;
};

out vec4 fragColor;

in vec3 fragPos;
in mat3 TBN;
in vec2 textureCoord;
in vec4 light_space_pos;

uniform Material material;
#define MAX_LIGHTS 1
uniform vec3 viewPos;

uniform PointLight light[MAX_LIGHTS];
uniform DirLight dirLight;
uniform float far_plane;

uniform sampler2D shadow_map;
uniform samplerCube shadow_cube;

vec3 calcPointLight(PointLight p_light, vec3 p_fragpos, vec3 p_viewpos);
vec3 calcDirLight(DirLight p_light, vec3 p_fragpos, vec3 p_viewpos);

float calcShadow(vec4 lsp);
float calcPointShadow(PointLight p_light, vec3 pos);

void main() {
	if (texture(material.texture_diffuse0, textureCoord).w < 0.5f) discard;
	vec3 result = calcDirLight(dirLight, fragPos, viewPos);
	for(int i = 0; i < MAX_LIGHTS; i++) {
		result += calcPointLight(light[i], fragPos, viewPos);
	}
	fragColor = vec4(result, texture(material.texture_diffuse0, textureCoord).w);
}

vec3 calcPointLight(PointLight p_light, vec3 p_fragpos, vec3 p_viewpos) {

	vec3 ambient = vec3(texture(material.texture_diffuse0, textureCoord)) * p_light.ambient;

	float lightDist = length(p_light.position - p_fragpos);
	vec3 lightDir = normalize(p_light.position - p_fragpos);
	vec3 normal = TBN * normalize(texture(material.texture_normal0, textureCoord).rgb * 2.0f - 1.0f);

	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diff * vec3(texture(material.texture_diffuse0, textureCoord)) * p_light.diffuse;

	vec3 viewDir = normalize(p_viewpos - p_fragpos);

	vec3 halfwayDir = normalize(viewDir + lightDir);
	float spec = pow(max(dot(halfwayDir, normal), 0.0f), material.shinyness);
	vec3 specular = spec * texture(material.texture_specular0, textureCoord).rrr * p_light.specular;

	float attenuation = 1.0f + lightDist * p_light.linear + lightDist * lightDist * p_light.quadratic;
	return (ambient + (diffuse + specular)*calcPointShadow(p_light, p_fragpos)) / attenuation;
}

vec3 calcDirLight(DirLight p_light, vec3 p_fragpos, vec3 p_viewpos) {

	vec3 ambient = vec3(texture(material.texture_diffuse0, textureCoord)) * p_light.ambient;

	vec3 lightDir = normalize(-p_light.direction);
	vec3 normal = TBN * normalize(texture(material.texture_normal0, textureCoord).rgb * 2.0f - 1.0f);

	float diff = max(dot(lightDir, normal), 0.0f);
	vec3 diffuse = diff * vec3(texture(material.texture_diffuse0, textureCoord)) * p_light.diffuse;

	vec3 viewDir = normalize(p_viewpos - p_fragpos);

	vec3 halfwayDir = normalize(viewDir + lightDir);
	float spec = pow(max(dot(halfwayDir, normal), 0.0f), material.shinyness);
	vec3 specular = spec * texture(material.texture_specular0, textureCoord).rrr * p_light.specular;

	return ambient + (diffuse + specular) * calcShadow(light_space_pos);
}

float calcShadow(vec4 lsp) {

	vec3 projCoords = lsp.xyz / lsp.w;

	if (projCoords.z > 1.0f) return 1.0f;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadow_map, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
	
	float shadow = 0.0;
	vec2 texelSize = 1.0f / textureSize(shadow_map, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadow_map, projCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - 0.005 > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 9.0;
	
    // // check whether current frag pos is in shadow
    // float shadow = currentDepth - 0.005 > closestDepth  ? 0.0f : 1.0f;

    return 1.0f - shadow;
}

float calcPointShadow(PointLight p_light, vec3 p_fragpos) {
	vec3 fragToLight = p_fragpos - p_light.position;
	float closestDepth = texture(shadow_cube, fragToLight).r;
	closestDepth *= far_plane;

	float currentDepth = length(fragToLight);

	if (currentDepth > far_plane) return 1.0f;

	float bias = 0.05f;
	return (currentDepth - bias > closestDepth) ? 0.0f : 1.0f;
}