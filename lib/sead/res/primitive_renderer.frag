uniform sampler2D texture0;
uniform float rate;

void main(void)
{
    vec4 color = texture2D(texture0, gl_TexCoord[0].st);
    gl_FragColor.r = gl_Color.r * (color.r * rate + (1 - rate));
    gl_FragColor.g = gl_Color.g * (color.g * rate + (1 - rate));
    gl_FragColor.b = gl_Color.b * (color.b * rate + (1 - rate));
    gl_FragColor.a = gl_Color.a * (color.a * rate + (1 - rate));
}
