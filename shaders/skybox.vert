layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in vec3 vertexNormal;

uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

out vec3 texCoords;

void main()
{ 
    gl_Position = projectionMatrix * modelViewMatrix * vertexPosition;;
    texCoords = vec3(vertexPosition.x, -vertexPosition.yz);
}
