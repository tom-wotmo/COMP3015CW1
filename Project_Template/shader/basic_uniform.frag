#version 460

layout (location = 0) out vec4 FragColor;


in vec3 position;
in vec3 normal;
in vec2 TexCoord;
 
//Light structure
uniform struct LightInfo 
{
  vec4 Position;		
  vec3 La;	//ambient light			
  vec3 L;	//light diffuse and spec			
} Lights;

//material information struct
uniform struct MaterialInfo 
{
  vec3 Ka; //material ambient				
  vec3 Kd; //material diffuse		
  vec3 Ks; //material specular			
  float Shininess; //material shininess	
} Material;
uniform struct FogInfo
{
float MaxDist;
float MinDist;
vec3 Colour;

}Fog;

 vec3 phongModel(vec3 pos, vec3 n)
 {
	
	 vec3 ambient = Lights.La * Material.Ka; 

	 vec3 s = normalize(vec3(Lights.Position) - pos);
	 float sDotN = max( dot(s,n), 0.0 );
	 vec3 diffuse = Material.Kd * sDotN;

	 vec3 spec = vec3(0.0);
	if( sDotN > 0.0 )
	{
	 vec3 v = normalize(-position.xyz);
	 vec3 r = reflect( -s, n );
	 spec = Material.Ks * pow( max( dot(r,v), 0.0 ),
	 Material.Shininess );
	}

	 return ambient + Lights.L * (diffuse + spec);
 }
void main()
{
  
    float dist = abs(position.z);

	float fogFactor = (Fog.MaxDist - dist) / (Fog.MaxDist - Fog.MinDist);

	fogFactor = clamp(fogFactor,0.0,1.0);

	vec3 phongColour = phongModel(position, normalize(normal));

	vec3 colour = mix(Fog.Colour, phongColour, fogFactor);

	FragColor = vec4(colour, 1.0);
}