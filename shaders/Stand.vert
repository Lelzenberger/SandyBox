layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

out vec3 fragPos;
out vec3 normal;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

void main()
{    
    gl_Position = projectionMatrix * modelViewMatrix * vertexPosition;
    normal = normalMatrix * vertexNormal;
    fragPos = vec3(modelViewMatrix * vertexPosition);
}
