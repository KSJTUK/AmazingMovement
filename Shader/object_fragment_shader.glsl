#version 460 core

const float lessThanZero = 0.000001f;

out vec4 FragColor;

in vec2 vs_out_texture;
in vec3 vs_out_normal;
in vec3 vs_out_fragPosition;

// 광원의 빛에 대한 계수들을 구조체로 묶음
struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct DirectionLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	
	// 거리에 따른 감쇠값 Attenuation 계산을 위한 3가지 변수 설정
	// 분자 == 1.0, 분모 == constant + linear * distance + linear * distance * distance
	float constant;		// 상수항, 거의 모든 경우에서 1.0유지, 최종 결과의 분모 값을 1보다 작게 만들지 않기 위한 장치
	float linear;		// 거리값과 곱해지며 1차원 적인 방법으로 세기 감쇠, linear * distance
	float quadratic;	// 거리값과 곱해지며 2차원 적으로 세기 감쇠 quadratic * distance * distance
};

// Spot Light 카메라를 기준으로 비추는 조명
struct FlashLight {
	vec3 position;
	vec3 direction;
	float cutOff; // cutOff -> value of result cos(theta) oper
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

// 오브젝트의 meterial속성을 구조체로 묶음
struct Meterials {
	sampler2D diffuse;
	vec3 specular;
	float shininess;
};

uniform vec3 objectColor;
uniform vec3 viewPosition;
uniform Meterials meterials;

uniform DirectionLight dirLight;
uniform PointLight pointLight;
uniform FlashLight spotLight;

uniform int notextureID;

vec3 calcDirectionLighting(DirectionLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	vec3 textureDiffuse = notextureID == 1 ? vec3(0.5f) : vec3(texture(meterials.diffuse, vs_out_texture));
	vec3 ambient = light.ambient * textureDiffuse;

	// 퐁모델의 디퓨즈 항
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(-light.direction);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * textureDiffuse);

	// 퐁모델의 스페큘러 항
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	return (ambient + diffuse + specular);
}

vec3 calcPointLighting(PointLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	vec3 ambient = light.ambient * vec3(texture(meterials.diffuse, vs_out_texture));

	// 퐁모델의 디퓨즈 항
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragPos);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * vec3(texture(meterials.diffuse, vs_out_texture)));

	// 퐁모델의 스페큘러 항
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	float dist = length(light.position - fragPos);
	float attenuationUnder = light.constant + light.linear * dist + light.quadratic * dist * dist;
	float attenuation = 1.0f / attenuationUnder;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);
}

vec3 calcFlashLighting(FlashLight light, vec3 normal, vec3 viewPos,  vec3 fragPos)
{
	vec3 lightDirection = normalize(light.position - fragPos);
	float theta = dot(lightDirection, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

	vec3 resultColor = vec3(0.0f);
	vec3 ambient = light.ambient * vec3(texture(meterials.diffuse, vs_out_texture));

	// 퐁모델의 디퓨즈 항
	vec3 vNorm = normalize(normal);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * vec3(texture(meterials.diffuse, vs_out_texture)));

	// 퐁모델의 스페큘러 항
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec =  pow(max(dot(viewDirection, reflectDirection), 0.0f), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	float dist = length(light.position - fragPos);
	float attenuationUnder = light.constant + light.linear * dist + light.quadratic * (dist * dist);
	float attenuation = 1.0f / attenuationUnder;

	// ambient *= attenuation; // remove ambient * attenuation
	diffuse *= intensity;
	specular *= intensity; 

	return ambient + diffuse + specular;
}

vec3 notexturePointLighting(PointLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	vec3 notexDiffuse = vec3(0.5f);

	vec3 ambient = light.ambient * notexDiffuse;

	// 퐁모델의 디퓨즈 항
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragPos);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * notexDiffuse);

	// 퐁모델의 스페큘러 항
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	float dist = length(light.position - fragPos);
	float attenuationUnder = light.constant + light.linear * dist + light.quadratic * dist * dist;
	float attenuation = 1.0f / attenuationUnder;

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	return (ambient + diffuse + specular);	
}


void main(void)
{
	vec3 resultColor = calcDirectionLighting(dirLight, vs_out_normal, viewPosition, vs_out_fragPosition);

	if (notextureID == 1) {
		resultColor += notexturePointLighting(pointLight, vs_out_normal, viewPosition, vs_out_fragPosition);
	} else {
		resultColor += calcPointLighting(pointLight, vs_out_normal, viewPosition, vs_out_fragPosition);
	}

	resultColor += calcFlashLighting(spotLight, vs_out_normal, viewPosition, vs_out_fragPosition);

	FragColor = vec4 (resultColor * objectColor, 1.0f);
}