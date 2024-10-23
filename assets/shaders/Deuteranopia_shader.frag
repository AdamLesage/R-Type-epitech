uniform sampler2D texture;

void main() {
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    float r = color.r * 0.8 + color.g * 0.2;
    float g = color.r * 0.3 + color.g * 0.7;
    float b = color.b;

    gl_FragColor = vec4(r, g, b, color.a);
}
