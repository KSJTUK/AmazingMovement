#version 460 core

const float lessThanZero = 0.000001f;

out vec4 FragColor;

in vec2 vs_out_texture;
in vec3 vs_out_normal;
in vec3 vs_out_fragPosition;

// ������ ���� ���� ������� ����ü�� ����
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
	
	// �Ÿ��� ���� ���谪 Attenuation ����� ���� 3���� ���� ����
	// ���� == 1.0, �и� == constant + linear * distance + linear * distance * distance
	float constant;		// �����, ���� ��� ��쿡�� 1.0����, ���� ����� �и� ���� 1���� �۰� ������ �ʱ� ���� ��ġ
	float linear;		// �Ÿ����� �������� 1���� ���� ������� ���� ����, linear * distance
	float quadratic;	// �Ÿ����� �������� 2���� ������ ���� ���� quadratic * distance * distance
};

// Spot Light ī�޶� �������� ���ߴ� ����
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

// ������Ʈ�� meterial�Ӽ��� ����ü�� ����
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

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(-light.direction);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * textureDiffuse);

	// ������ ����ŧ�� ��
	vec3 viewDirection = normalize(viewPos - fragPos);
	vec3 reflectDirection = reflect(-lightDirection, vNorm);
	float spec = pow(max(dot(viewDirection, reflectDirection), 0.0f), meterials.shininess);
	vec3 specular = spec * (light.specular * meterials.specular);

	return (ambient + diffuse + specular);
}

vec3 calcPointLighting(PointLight light, vec3 normal, vec3 viewPos, vec3 fragPos)
{
	vec3 ambient = light.ambient * vec3(texture(meterials.diffuse, vs_out_texture));

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragPos);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * vec3(texture(meterials.diffuse, vs_out_texture)));

	// ������ ����ŧ�� ��
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

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * vec3(texture(meterials.diffuse, vs_out_texture)));

	// ������ ����ŧ�� ��
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

	// ������ ��ǻ�� ��
	vec3 vNorm = normalize(normal);
	vec3 lightDirection = normalize(light.position - fragPos);

	float diffuseN = max(dot(vNorm, lightDirection), 0.0f);
	vec3 diffuse = light.diffuse * (diffuseN * notexDiffuse);

	// ������ ����ŧ�� ��
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