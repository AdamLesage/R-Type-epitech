uniform sampler2D texture;

void main() {
    vec4 color = texture2D(texture, gl_TexCoord[0].xy);

    float r = color.r * 0.567 + color.g * 0.433;
    float g = color.r * 0.558 + color.g * 0.442;
    float b = color.b;

    gl_FragColor = vec4(r, g, b, color.a);
}
