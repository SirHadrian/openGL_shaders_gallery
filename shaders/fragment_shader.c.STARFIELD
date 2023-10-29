#version 460 core
layout(location = 0) out vec4 FragColor;

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

#define T u_time
#define R u_resolution
#define FC gl_FragCoord
#define M u_mouse

#define PI 3.14159265359
#define S(a, b, x) smoothstep(a, b, x)

#define GRID_LIMIT .49
#define STAR_LAYER 4.

float hash(vec2 seed) {

  vec2 r1 = vec2(3424.12, 2434.23);
  float r2 = 7342.64;

  return fract(sin(dot(seed, r1)) * r2);
}

float star(vec2 gv) {

  float d = length(gv);

  float m = .05 / d;

  return m *= S(1., .2, d);
}

vec3 starLayer(vec2 uv) {

  vec3 color = vec3(0);

  vec2 id = floor(uv);
  vec2 gv = fract(uv) - .5;

  for (float y = -1.; y <= 1.; y += 1.) {
    for (float x = -1.; x <= 1.; x += 1.) {

      vec2 o = vec2(x, y);

      float n = hash(id + o);

      vec2 of = vec2(n, fract(n * 3143.34)) - .5;

      float star = star(gv - of - o);

      vec3 c = sin(vec3(0.4, 0.2, 0.5) * fract(n * 4532.) * 34234.) * .5 + .5;
      c += c + (sin(T * 2. + n * 34234.32) * .5 + .5) * .5;

      float size = fract(n * 31.34);

      color += star * c * size;
    }
  }

  return color;
}

void main() {

  vec2 uv = (FC.xy - .5 * R.xy) / R.y;

  vec3 color = vec3(0.);

  uv *= 4.;

  for (float i = 0.; i < 1.; i += 1. / STAR_LAYER) {

    float depth = fract(i + T * .2);

    float s = mix(5., .1, depth);

    color += starLayer(uv * s + i * 341.43) * depth * S(1., .9, depth);
  }

  FragColor = vec4(color, 1.);
}
