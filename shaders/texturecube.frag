uniform samplerCube textureMap;

in vec3 texCoords;
out vec4 fragColor;

void main()
{
        vec4 textureFrag = texture(textureMap, texCoords);
        fragColor = vec4(textureFrag.rgb, textureFrag.a);
}
