#version 330 core
out vec4 FragColor;

in vec3 s_TexCoords;
in vec4 fragPos;

uniform samplerCube skybox;
uniform vec3 viewPos;


float CalcLinearFog();
float CalcExpoFog();
//Fog
uniform float fogDensity = 0.66;
uniform float fogStart = 8.0;
uniform float fogEnd = 40;
uniform vec3 fogColor = vec3(152.0/256.0,152.0/256.0,152.0/256.0);
uniform bool fogActive = false;
void main()
{    
      vec4 dif = texture(skybox, s_TexCoords);
       float fogFactor = 1;
      if(fogActive)
      {
        fogFactor = CalcLinearFog();

      }
      else
      {  
         fogFactor = 1;

      }

      vec4 result = mix(vec4(fogColor,1.0),dif,fogFactor);

       FragColor = result;
}

float CalcLinearFog()
{

   float camDist = length(fragPos.xyz - viewPos);
   float fogRange = fogEnd - fogStart;
   float fogDist = fogEnd - camDist;
   float fogFactor = fogDist /fogRange;
   fogFactor  = clamp(fogFactor,0.0,1.0);
   return fogFactor;
}


float CalcExpoFog()
{
   float camDist = length(fragPos.xyz - viewPos);
   float distRatio = 4.0 * camDist / fogEnd;
   float fogFactor = exp(-distRatio * fogDensity * distRatio * fogDensity);

   return fogFactor;
 
}
