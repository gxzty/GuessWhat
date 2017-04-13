#ifdef GL_ES
precision mediump float;
#endif

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

//uniform sampler2D CC_Texture0;
uniform vec2 resolution;

void main() {
    gl_FragColor = mainImage(v_fragmentColor, v_texCoord);
}




vec3 draw(vec2 uv) {
    return texture2D(CC_Texture0,vec2(uv.x,1.-uv.y)).rgb;   
    //return texture(iChannel0,uv).rgb;  
}

float grid(float var, float size) {
    return floor(var*size)/size;
}

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

vec4 mainImage(vec2 fragCoord , vec2 uv)
{
    
    float bluramount = 0.1;

    //float dists = 5.;
    vec3 blurred_image = vec3(0.);
    #define repeats 60.
    for (float i = 0.; i < repeats; i++) { 
        //Older:
        //vec2 q = vec2(cos(degrees((grid(i,dists)/repeats)*360.)),sin(degrees((grid(i,dists)/repeats)*360.))) * (1./(1.+mod(i,dists)));
        vec2 q = vec2(cos(degrees((i/repeats)*360.)),sin(degrees((i/repeats)*360.))) *  (rand(vec2(i,uv.x+uv.y))+bluramount); 
        vec2 uv2 = uv+(q * bluramount);
        blurred_image += draw(uv2)/2.;
        //One more to hide the noise.
        q = vec2(cos(degrees((i/repeats)*360.)),sin(degrees((i/repeats)*360.))) *  (rand(vec2(i+2.,uv.x+uv.y+24.))+bluramount); 
        uv2 = uv+(q*bluramount);
        blurred_image += draw(uv2)/2.;
    }
    blurred_image /= repeats;
        
    fragColor = vec4(blurred_image,1.0);
    return fragColor;
}