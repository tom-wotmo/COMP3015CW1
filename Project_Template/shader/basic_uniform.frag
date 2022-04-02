#version 460

layout (location = 0) out vec4 FragColor;
layout (binding = 0) uniform sampler2D Tex1;

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

 vec3 blinnPhongModel(vec3 pos, vec3 n)
{
     
	 //getting the colour of texture
	 vec3 texColour = texture(Tex1, TexCoord).rgb;

	 //ambient calculation
	 vec3 ambient = texColour * Lights.La; 

	
	 vec3 s = vec3 (0.0);
	 s = normalize(vec3(Lights.Position) - pos);
	 
	 //dot product
	 float sDotN = max( dot(s,n), 0.0 );

	 vec3 diffuse = texColour * sDotN;

	 vec3 spec = vec3(0.0);

	 vec3 v = normalize(-position.xyz);

	if( sDotN > 0.0 )
	{

	 vec3 h = normalize(v + s);

	 //calculate specular
	 spec = Material.Ks * pow( max( dot(h,normal), 0.0 ), Material.Shininess);

	}

	 return ambient + Lights.L * (diffuse + spec);
 }
void main()
{
  
    //calculating the fog
    float dist = abs(position.z);

	float fogFactor = (Fog.MaxDist - dist) / (Fog.MaxDist - Fog.MinDist);

	fogFactor = clamp(fogFactor,0.0,1.0);

	//passing into the phong model
	vec3 phongColour = blinnPhongModel(position, normalize(normal));

	//combining our fog colour and blinnphong
	vec3 colour = mix(Fog.Colour, phongColour, fogFactor);

	FragColor = vec4(colour, 1.0);
}