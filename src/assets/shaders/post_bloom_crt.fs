VARYING vec2 fragTexCoord;
VARYING vec4 fragColor;

uniform sampler2D texture0;

const vec2 RESOLUTION = vec2(640.0, 360.0);

const float BLOOM_THRESHOLD = 0.50;
const float BLOOM_INTENSITY = 0.50;

const float SCANLINE_INTENSITY = 0.18;
const float VIGNETTE_INTENSITY = 0.28;
const float CURVATURE = 0.18;
const float CHROMATIC_ABERRATION = 0.00;
const float NOISE_INTENSITY = 0.018;

float Luma(vec3 color)
{
    return dot(color, vec3(0.299, 0.587, 0.114));
}

vec2 CurveUv(vec2 uv)
{
    vec2 centered = uv * 2.0 - 1.0;

    vec2 offset = abs(centered.yx) / vec2(6.0, 4.0);
    centered += centered * offset * offset * CURVATURE;

    return centered * 0.5 + 0.5;
}

vec3 SampleSafe(vec2 uv)
{
    uv = clamp(uv, vec2(0.0), vec2(1.0));
    return TEXTURE(texture0, uv).rgb;
}

void AddBloomSample(inout vec3 bloom, vec2 uv)
{
    vec3 color = SampleSafe(uv);

    float brightness = Luma(color);
    float mask = smoothstep(BLOOM_THRESHOLD, 1.0, brightness);

    bloom += color * mask;
}

vec3 SampleBloom(vec2 uv)
{
    vec2 texel = 1.0 / RESOLUTION;

    vec3 bloom = vec3(0.0);

    AddBloomSample(bloom, uv + vec2( 1.0,  0.0) * texel);
    AddBloomSample(bloom, uv + vec2(-1.0,  0.0) * texel);
    AddBloomSample(bloom, uv + vec2( 0.0,  1.0) * texel);
    AddBloomSample(bloom, uv + vec2( 0.0, -1.0) * texel);

    AddBloomSample(bloom, uv + vec2( 2.0,  0.0) * texel);
    AddBloomSample(bloom, uv + vec2(-2.0,  0.0) * texel);
    AddBloomSample(bloom, uv + vec2( 0.0,  2.0) * texel);
    AddBloomSample(bloom, uv + vec2( 0.0, -2.0) * texel);

    AddBloomSample(bloom, uv + vec2( 1.5,  1.5) * texel);
    AddBloomSample(bloom, uv + vec2(-1.5,  1.5) * texel);
    AddBloomSample(bloom, uv + vec2( 1.5, -1.5) * texel);
    AddBloomSample(bloom, uv + vec2(-1.5, -1.5) * texel);

    return bloom / 12.0;
}

float Random(vec2 uv)
{
    return fract(
        sin(dot(uv, vec2(12.9898, 78.233))) *
        43758.5453
    );
}

void main()
{
    vec2 uv = fragTexCoord;

    uv = CurveUv(uv);

    if(uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0)
    {
        FRAGCOLOR = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    vec2 texel = 1.0 / RESOLUTION;

    float r = SampleSafe(
        uv + vec2(texel.x * CHROMATIC_ABERRATION, 0.0)
    ).r;

    float g = SampleSafe(uv).g;

    float b = SampleSafe(
        uv - vec2(texel.x * CHROMATIC_ABERRATION, 0.0)
    ).b;

    vec3 color = vec3(r, g, b);

    vec3 bloom = SampleBloom(uv);
    color += bloom * BLOOM_INTENSITY;

    float scanline =
        sin(uv.y * RESOLUTION.y * 3.14159265);

    scanline =
        1.0 - SCANLINE_INTENSITY * (0.5 + 0.5 * scanline);

    color *= scanline;

    float vignette =
        distance(uv, vec2(0.5));

    vignette =
        smoothstep(0.85, 0.25, vignette);

    color *= mix(1.0, vignette, VIGNETTE_INTENSITY);

    float noise =
        Random(gl_FragCoord.xy) - 0.5;

    color += noise * NOISE_INTENSITY;

    color = clamp(color, 0.0, 1.0);

    FRAGCOLOR = vec4(color, 1.0);
}