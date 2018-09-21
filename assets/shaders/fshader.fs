#version 330 core

out vec4 fragColor;

uniform sampler2D text2d;

void main() {
	
	fragColor = texture(text2d, gl_FragCoord.xy/1000.0f);
}