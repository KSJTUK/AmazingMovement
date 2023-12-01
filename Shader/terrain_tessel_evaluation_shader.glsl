#version 460 core

layout (quads, fractional_odd_spacing, ccw) in;

in vec2 tcs_out_tex[];
in vec3 tcs_out_normal[];

out vec2 tes_out_tex;
out vec3 tes_out_normal;

out float height;
out float heightFactor;

uniform sampler2D heightMap;
uniform mat4 perspective;

vec3 calcTessellationedNormal(vec3 cp0, vec3 cp1, vec3 cpNormal0, vec3 cpNormal1)
{
    vec3 dirVec = cp0 - cp1;
    vec3 addNormal = cpNormal0 + cpNormal1;
    vec3 normal = addNormal - (2 * (dot(addNormal, dirVec) / dot(dirVec, dirVec))) * dirVec;
    return normal;
}

void main()
{
    // 가중치 (선형 보간할 계수들)를 받아옴
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;

    // 컨트롤 포인트들의 텍스쳐 좌표들
    vec2 t00 = tcs_out_tex[0];
    vec2 t01 = tcs_out_tex[1];
    vec2 t10 = tcs_out_tex[2];
    vec2 t11 = tcs_out_tex[3];

    // 새로 생성될 프리미티브의 텍스쳐 좌표를 선형보간하여 계산함
    vec2 t0 = (t01 - t00) * u + t00;
    vec2 t1 = (t11 - t10) * u + t10;
    vec2 texCoord = (t1 - t0) * v + t0;

    // 하이트 맵에서 텍스쳐 색상을 받아옴
    heightFactor = 64.0f;
    height = texture(heightMap, texCoord).x * heightFactor - heightFactor / 2.0f;

    // 컨트롤 포인트
    vec4 p00 = gl_in[0].gl_Position;
    vec4 p01 = gl_in[1].gl_Position;
    vec4 p10 = gl_in[2].gl_Position;
    vec4 p11 = gl_in[3].gl_Position;

    // 사각형이므로 두 엣지들의 외적값으로 노멀을 계산
    vec4 uVec = p01 - p00;
    vec4 vVec = p10 - p00;
    vec4 normal = normalize( vec4(cross(uVec.xyz, vVec.xyz), 0) );


    vec4 p0 = (p01 - p00) * u + p00;
    vec4 p1 = (p11 - p10) * u + p10;
    vec4 p = (p1 - p0) * v + p0 + normal * height;

    gl_Position = perspectiveMat * p;

    tes_out_tex = texCoord;
    tes_out_normal = vec3(normal);
}