#version 120

// https://www.shadertoy.com/view/XdSGzh
// Lissajous curve
// http://en.wikipedia.org/wiki/Lissajous_curve

//uniform sampler2DRect tex0;
varying vec2 texCoordVarying;
const float PI = 3.14159;
const int steps = 200;

uniform vec4 iMouse;
uniform vec3 iResolution;
uniform float iGlobalTime;

vec2 lissajous(float t, float a, float b, float d)
{
	return vec2(sin(a*t+d), sin(b*t));
}

//void mainImage( out vec4 fragColor, in vec2 fragCoord )
void main()
{
//	vec2 uv = (fragCoord.xy / iResolution.xy)*2.0-1.0;

    // get coordinates?
	vec2 uv = (gl_FragCoord.xy / iResolution.xy)*2.0-1.0;
	uv.x *= iResolution.x / iResolution.y;
	vec2 mouse = iMouse.xy / iResolution.xy;

	float a = 2.0;
	float b = 3.0;
	float d = iGlobalTime;	// phase
	
	if (iMouse.z > 0.0) {
		a = 1.0 + mouse.x*3.0;
		b = 1.0 + mouse.y*3.0;
	}
	
	float m = 1.0;
	float period = PI*2.0;
    vec2 lp = lissajous(iGlobalTime, a, b, d)*0.8;
    for(int i = 1; i <= steps; i++) 
    {
        float t = float(i)*period / float(steps);
		t += iGlobalTime;
        vec2 p = lissajous(t, a, b, d)*0.8;
		
		// distance to line
        vec2 pa = uv - p;
        vec2 ba = lp - p;
        float h = clamp( dot(pa,ba)/dot(ba,ba), 0.0, 1.0 );
        vec2 q = pa - ba*h;
        m = min( m, dot( q, q ) );
		
        lp = p;
    }
    m = sqrt( m );
	m = smoothstep(0.01, 0.0, m);
	
//	fragColor = mix(vec4(0.0), vec4(0.2, 1.0, 0.1, 1.0), m);
	gl_FragColor = mix(vec4(0.0), vec4(0.2, 1.0, 0.1, 1.0), m);
}