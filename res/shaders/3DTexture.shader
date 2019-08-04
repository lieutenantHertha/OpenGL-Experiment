#shader vertex
#version 330 core
layout(location = 0) in  vec3 vertexPosition;
layout(location = 1) in  vec2 texCoord;
                     out vec2 v_TexCoord;
                     uniform mat4 u_ModelMatrix;
                     uniform mat4 u_ViewMatrix;
                     uniform mat4 u_ProjMatrix;
void main()
{
	gl_Position = u_ProjMatrix * u_ViewMatrix * u_ModelMatrix * vec4(vertexPosition, 1.00f);
	v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
                     in  vec2 v_TexCoord;
                     uniform sampler2D u_Texture1;
					 uniform sampler2D u_Texture2;
void main()
{
	vec4 texColor1 = texture(u_Texture1, v_TexCoord);
	vec4 texColor2 = texture(u_Texture2, v_TexCoord);
	color = texColor1 * texColor2;
};