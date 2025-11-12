#version 400 core
#define MAX_LIGHTS 20

in vec3 worldPos;
in vec3 worldNor;
out vec4 fragColor;

uniform vec3 uViewPos;
uniform vec4 uObjectColor;
uniform vec3 uAmbientColor;
uniform float uShininess;
uniform float uSpecularStrength;

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
    vec3 V = normalize(uViewPos - worldPos);

    vec3 ambient = uAmbientColor;
    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    for (int i = 0; i < numberOfLights; i++)
    {
        vec3 L = normalize(lights[i].position - worldPos);
        vec3 R = reflect(-L, N);
        float NdotL = dot(N, L);

        float lightDistance = length(lights[i].position - worldPos);
        float attenuation = 1.0 / (lights[i].constant + lights[i].linear * lightDistance + lights[i].quadratic * (lightDistance * lightDistance));

        float spec = 0.0;
        if (NdotL > 0.0) {
            spec = pow(max(dot(V, R), 0.0), uShininess);
        }

        float diff = max(NdotL, 0.0);

        vec3 diffuse = diff * lights[i].color * uObjectColor.rgb;
        vec3 specular = uSpecularStrength * spec * lights[i].color;

        //Flashlight only
        if (lights[i].type == 1) { 
            float dotLF = dot(normalize(-L), normalize(lights[i].direction));

            float alpha = lights[i].outerCutoff;
            float beta  = lights[i].innerCutoff;

            float intensity = (dotLF - alpha) / (beta - alpha);
            intensity = clamp(intensity, 0.0, 1.0);

            diffuse  *= intensity;
            specular *= intensity;
        }
        //End of flash light part

        totalDiffuse += diffuse * attenuation;
        totalSpecular += specular * attenuation;
    }

    vec3 result = ambient + totalDiffuse + totalSpecular;
    fragColor = vec4(result, 1.0);
}