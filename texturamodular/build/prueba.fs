#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

// texture sampler
uniform sampler2D texture1;
uniform sampler2D texture2;
void main()
{
	vec4 color1 = texture(texture1, TexCoord); // Obtener color de la primera textura
    vec4 color2 = texture(texture2, TexCoord); // Obtener color de la segunda textura
    if(color1.a < 0.1)
        discard;
    // Mezcla 80% de color1 y 20% de color2
    FragColor = color1;

}

