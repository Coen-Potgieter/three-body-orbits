
uniform vec2 u_center;
uniform float u_radius;
uniform vec4 u_color;

void main() {
    float dist = distance(gl_FragCoord.xy, u_center);
    float intensity = 1.0 - smoothstep(0.0, u_radius, dist);
    gl_FragColor = vec4(u_color.rgb, intensity * u_color.a);
}

