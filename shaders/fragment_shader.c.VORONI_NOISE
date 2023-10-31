#version 460 core
layout(location = 0) out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;
// Load texture
// vec4 text = texture(tex0, texCoord * vec2(-1., 1.));

uniform float u_time;
uniform vec2 u_resolution;
uniform vec2 u_mouse;

#define T u_time
#define R u_resolution
#define FC gl_FragCoord
#define M u_mouse

#define PI 3.14159265359
#define S(a, b, x) smoothstep(a, b, x)

float 
hash(vec2 seed) 
{
  vec2 m1 = vec2(324345., 435424.);
  float m2 = 345232.;

  return fract(sin(dot(seed, m1)) * m2);
}

vec2 
noise2x2(vec2 p) 
{
  float x = dot(p, vec2(123.4, 234.5));
  float y = dot(p, vec2(345.6, 456.7));
  vec2 noise = vec2(x, y);
  noise = sin(noise);
  noise = noise * 43758.5453;
  noise = fract(noise);
  return noise;
}

void 
main() 
{
  vec2 uv = FC.xy / R.xy;
  uv -= .5;
  uv.x *= R.x / R.y;

  vec3 color = vec3(0.);

  uv = uv * 8.0;

  vec2 id = floor(uv);
  vec2 gv = fract(uv) - .5;

  // part 2.1 - add a point at the center of each grid
  float points = 0.0;
  float min_dist = 100.0;

  for (float i = -1.0; i <= 1.0; i++) {
    for (float j = -1.0; j <= 1.0; j++) {
      vec2 neighbor = vec2(i, j);

      vec2 noise = noise2x2(id + neighbor);
      vec2 point = neighbor + sin(T * noise) * 0.5;

      float dist = length(gv - point);
      min_dist = min(dist, min_dist);

      points += smoothstep(0.95, 0.96, 1.0 - dist);
    }
  }

  // color = vec3(min_dist);
  color = vec3(smoothstep(0.0, 1.0, min_dist));

  color = vec3(smoothstep(0.25, 1.0, 1.0 - min_dist));

  FragColor = vec4(color, 1.);
}
