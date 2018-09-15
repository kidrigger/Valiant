#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec3 aTang;
layout (location = 3) in vec3 aBitan;
layout (location = 4) in vec2 aTex;

out vec3 fragPos;
out mat3 TBN;
out vec2 textureCoord;
out vec3 col;
out vec4 light_space_pos;

uniform mat4 mvp;
uniform mat4 model;
uniform mat4 normal_model;

uniform sampler2D shadow_map;
uniform mat4 shadow_mvp;

void main() {
	gl_Position = mvp * vec4(aPos, 1.0f);
	fragPos = vec3(model * vec4(aPos, 1.0f));
	
	vec3 N = normalize(mat3(normal_model) * aNorm);
	vec3 T = normalize(mat3(normal_model) * aTang);
	vec3 B = normalize(mat3(normal_model) * aBitan);
	T = T * ((dot(cross(N, T), B) < 0.0F) ? -1.0F : 1.0F);
	TBN = mat3(T, B, N);

	light_space_pos = shadow_mvp * vec4(aPos, 1.0f);
	textureCoord = aTex;
}
