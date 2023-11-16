#version 430

// Input
layout(location = 0) in vec2 texture_coord;
// TODO (student): wait for the normal input

// Uniform properties
uniform sampler2D text;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    vec4 color = texture2D(text, texture_coord);

    if (color.a < 0.5)
    {
        discard;
    }

    out_color = color;
}
