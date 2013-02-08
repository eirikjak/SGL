#version 330

in vec4 coord4d;
in float normal;
uniform mat4 mvp;
uniform mat4 modelMatrix;


out vec4 f_texcoord;
out float f_normalIndex;
out vec4 f_normal;
out vec4 f_position;
vec4 normals[6] = vec4[](
	vec4(-1.0,0.0,0.0,0.0),
	vec4(1.0,0.0,0.0,0.0),
	vec4(0.0,0.0,-1.0,0.0),
	vec4(0.0,0.0,1.0,0.0),
	vec4(0.0,1.0,0.0,0.0),
	vec4(0.0,-1.0,0.0,0.0)


);

void main()
{
	
	f_normal = normalize(modelMatrix*vec4(normals[int(normal)].xyz,0.0));
	f_position = modelMatrix*vec4(coord4d.xyz,1.0);
	f_normalIndex = normal;
	f_texcoord = coord4d;
	gl_Position    = mvp*vec4(coord4d.xyz,1.0);

}
