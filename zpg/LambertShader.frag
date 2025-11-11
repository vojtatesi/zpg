#version 400 core
#define MAX_LIGHTS 20

in vec3 worldPos;
in vec3 worldNor;

out vec4 fragColor;

uniform vec4 uObjectColor;
uniform vec3 uAmbientColor;

struct Light {
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
    int type; // 0 = Point, 1 = Flash

    vec3 direction;
    float innerCutoff;
    float outerCutoff;
};

uniform Light lights[MAX_LIGHTS];
uniform int numberOfLights;

void main() {
    vec3 N = normalize(worldNor);
    vec3 ambient = uAmbientColor;
    vec3 totalDiffuse = vec3(0.0);
   
    for(int i = 0; i < numberOfLights; i++){

        vec3 L = normalize(lights[i].position - worldPos);

        float diff = max(dot(N, L), 0.0);

        float lightDistance = length(lights[i].position - worldPos);
        float attenuation = 1.0 / (lights[i].constant + lights[i].linear * lightDistance + lights[i].quadratic * (lightDistance * lightDistance));


        vec3 diffuse = diff * lights[i].color * uObjectColor.rgb;

                //Flashlight only
        if (lights[i].type == 1) { 
            float dotLF = dot(normalize(-L), normalize(lights[i].direction));

            float alpha = lights[i].outerCutoff;
            float beta  = lights[i].innerCutoff;

            float intensity = (dotLF - alpha) / (beta - alpha);
            intensity = clamp(intensity, 0.0, 1.0);

            diffuse  *= intensity;
        }
        //End of flash light part

        totalDiffuse += diffuse * attenuation;        
    }

    vec3 result = ambient + totalDiffuse;
    fragColor = vec4(result, 1.0);
}