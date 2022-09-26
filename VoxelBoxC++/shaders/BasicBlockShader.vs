#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormals;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec2 aAtlasIndex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 TexCoord;


void main()
{
	vec2 atlasTexCoord = vec2((aTexCoord.x / 16.0f) + ((1.0f/ 16.0f) * aAtlasIndex.x), (aTexCoord.y / 16.0f) + ((1.0f / 16.0f) * aAtlasIndex.y));
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	TexCoord = atlasTexCoord;
}