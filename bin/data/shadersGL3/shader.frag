#version 150
// #version 120

// uniform vec4 globalColor;
// uniform float time;

uniform vec3 iResolution;
uniform float iGlobalTime;
uniform float iAmp;
uniform float iContra;
uniform float iBass;
uniform float iTenor;
uniform float iAlto;
uniform float iMezzo;
uniform float iSoprano;
uniform float iSopranino;
out vec4 outputColor;


vec3 hash33(vec3 p){
  float n = sin(dot(p, vec3(7, 157, 113)));    
  return fract(vec3(2097152, 262144, 32768)*n); 
}


float map(vec3 p){
  vec3 o = hash33(floor(p))*0.2; 
  p = fract(p + o)-.5; 
  float r = dot(p, p) - 0.21;
  p = abs(p); 
  return max(max(p.x, p.y), p.z)*.95 + r*0.05 - 0.21;
}


void main() {
  vec2 uv = (gl_FragCoord.xy - iResolution.xy*.5 )/iResolution.y;
  vec3 rd = normalize(vec3(uv, (1.-dot(uv, uv)*0.5*iGlobalTime)*.5));
  vec3 ro = vec3(0., 0., iGlobalTime*0.), col = vec3(0), sp;
  float cs = sin( iAlto*0.375 ), si = sin( iGlobalTime*0.375 );    
  rd.xz = mat2(cs, si,-si, cs)*rd.xz;
  rd.xy = mat2(cs, si,-si, cs)*rd.xy;
  rd *= 0.985 + hash33(rd)*0.03;
  float t=0., layers=0., d, aD;
  float thD = .035;	
  for(float i=0.; i<56.; i++)	{
    if(layers>15. || col.x > 1. || t>10.) break;
    sp = ro + rd*t;
    d = map(sp);        
    aD = (thD-abs(d)*15./16.)/thD;
    if(aD>0.) { 
      col += aD*aD*(3.-2.*aD)/(1. + t*t*0.25)*.2; 
      layers++; 
    }
    t += max(abs(d)*.7, thD*1.5); 
  }
    
  col = max(col, 0.);
  col = mix(col, vec3(min(col.x*1.5, 1.), pow(col.x, 2.5), pow(col.x, 12.)), 
	    dot(sin(rd.yzx*8. + sin(rd.zxy*8.)), vec3(iGlobalTime*.1666))+iSopranino);
  col = mix(col, vec3(col.x*col.x*.85, col.x, col.x*col.x*0.3), 
	    dot(sin(rd.yzx*4. + sin(rd.zxy*4.)), vec3(.1666))+0.25);
  outputColor = vec4( clamp(col, 0., 1.), 1.0 );
}


