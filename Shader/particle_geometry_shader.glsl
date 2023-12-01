#version 460 core

layout(points) in;
layout(points, max_vertices=4) out;
//layout(triangle_strip, max_vertices=3) out;
//layout(points, max_vertices=1) out;

in vec4 vs_out_color[];
in vec2 vs_out_tex[];

out vec4 gs_out_color;
out vec2 gs_out_tex;

float primitiveSize = 0.1f;
uniform float u_primiriveSize;

void createPoint(int index)
{
		gl_Position = gl_in[index].gl_Position + vec4(0.0f, primitiveSize, 0.0f, 0.0f);

		gs_out_color = vs_out_color[index];
		gs_out_tex = vs_out_tex[index];

		EmitVertex();
}

void createTriangle(int index)
{
		gl_Position = gl_in[index].gl_Position + vec4(0.0f, primitiveSize, 0.0f, 0.0f);

		gs_out_color = vs_out_color[index];
		gs_out_tex = vs_out_tex[index];

		EmitVertex();

		gl_Position = gl_in[index].gl_Position + vec4(-primitiveSize, -primitiveSize, 0.0f, 0.0f);

		gs_out_color = vs_out_color[index];
		gs_out_tex = vs_out_tex[index];

		EmitVertex();

		gl_Position = gl_in[index].gl_Position + vec4(primitiveSize, -primitiveSize, 0.0f, 0.0f);

		gs_out_color = vs_out_color[index];
		gs_out_tex = vs_out_tex[index];

		EmitVertex();
}

void createRectangle(int index)
{
		gl_Position = gl_in[index].gl_Position + vec4(-primitiveSize, primitiveSize, 0.0f, 0.0f);

		gs_out_color = vs_out_color[index];
		gs_out_tex = vs_out_tex[index];

		EmitVertex();

		gl_Position = gl_in[index].gl_Position + vec4(-primitiveSize, -primitiveSize, 0.0f, 0.0f);

		gs_out_color = vs_out_color[index];
		gs_out_tex = vs_out_tex[index];

		EmitVertex();

		gl_Position = gl_in[index].gl_Position + vec4(primitiveSize, primitiveSize, 0.0f, 0.0f);

		gs_out_color = vs_out_color[index];
		gs_out_tex = vs_out_tex[index];

		EmitVertex();

		gl_Position = gl_in[index].gl_Position + vec4(primitiveSize, -primitiveSize, 0.0f, 0.0f);

		gs_out_color = vs_out_color[index];
		gs_out_tex = vs_out_tex[index];

		EmitVertex();
}

void createSnowParticle(int index)
{
	gl_Position = gl_in[index].gl_Position + vec4(-primitiveSize, 0.0f, 0.0f, 0.0f);

	gs_out_color = vs_out_color[index];
	gs_out_tex = vs_out_tex[index];

	EmitVertex();

	gl_Position = gl_in[index].gl_Position + vec4(0.0f, -primitiveSize, 0.0f, 0.0f);

	gs_out_color = vs_out_color[index];
	gs_out_tex = vs_out_tex[index];

	EmitVertex();

	gl_Position = gl_in[index].gl_Position + vec4(primitiveSize, 0.0f, 0.0f, 0.0f);

	gs_out_color = vs_out_color[index];
	gs_out_tex = vs_out_tex[index];

	EmitVertex();

	gl_Position = gl_in[index].gl_Position + vec4(0.0f, primitiveSize, 0.0f, 0.0f);

	gs_out_color = vs_out_color[index];
	gs_out_tex = vs_out_tex[index];

	EmitVertex();	
}

void main(void)
{
	int inputPrimitives = gl_in.length();
	for (int i = 0; i < inputPrimitives; ++i) { 
//		createRectangle(i);
//		createTriangle(i);
		createSnowParticle(i);
	}
	EndPrimitive();
}