#sginclude "://shaders/commonlight.vert.inc"

// procedural brick texture
// inspired by ch. 6 in the orange book

out vec2 Pos_mc;   //Pos. in model coord.


void main()
{
    Pos_mc = vertexPosition.xy;
    gl_Position = vPos();
}
