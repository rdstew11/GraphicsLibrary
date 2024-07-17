#version 330 core

out vec4 FragColor;

in vec2 textureCoord;
in vec3 vertColor;

uniform sampler2D objTexture;

void main()
{
    FragColor = texture(objTexture, textureCoord);
}
