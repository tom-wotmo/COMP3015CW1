#version 460


in vec3 position;
in vec3 normal;

layout (location = 0) out vec4 FragColor;
 
//Light structure
uniform struct LightInfo 
{
  vec4 Position;		
  vec3 La;				
  vec3 L;				
} Lights;

//material information struct
uniform struct MaterialInfo 
{
  vec3 Ka;				
  vec3 Kd;		
  vec3 Ks;			
  float Shininess;	
} Material;

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
  
	FragColor = vec4(phongModel(position, normal), 1.0);
}