uniform sampler2D texture;

void main() {
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    float r = color.r;
    float g = color.g * 0.95 + color.b * 0.05;
    float b = color.g * 0.05 + color.b * 0.95;

    gl_FragColor = vec4(r, g, b, color.a);
}
