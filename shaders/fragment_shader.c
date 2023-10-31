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

void 
main() 
{
  vec2 uv = FC.xy / R.xy;
  uv -= .5;
  uv.x *= R.x / R.y;

  vec3 color = vec3(0.);

  vec2 id = floor(uv);
  vec2 gv = fract(uv);




  FragColor = vec4(color, 1.);
}
